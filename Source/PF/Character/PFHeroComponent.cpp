// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHeroComponent.h"
#include "PF/PFLogChannels.h"
#include "PF/PFGameplayTags.h"
#include "PF/Character/PFPawnExtensionComponent.h"
#include "PF/Character/PFPawnData.h"
#include "PF/Player/PFPlayerState.h"
#include "Components/GameFrameworkComponentManager.h"
//Camera
#include "PF/Camera/PFCameraMode.h"
#include "PF/Camera/PFCameraComponent.h"
//Input
#include "PF/Player/PFPlayerController.h"
#include "PF/Input/PFEnhancedInputComponent.h"
#include "PF/Input/PFInputConfig.h"
#include "PF/Input/PFMappableConfigPair.h"
#include "PlayerMappableInputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


const FName UPFHeroComponent::Name_ActorFeatureName("HeroComponent");
const FName UPFHeroComponent::Name_BindInputsNow("BindInputsNow");

UPFHeroComponent::UPFHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UPFHeroComponent::OnRegister()
{
	Super::OnRegister();
	
	{

		if (!GetPawn<APawn>()) // OwnerPawn이 존재하지 않는다면,
		{
			UE_LOG(PFLog, Error, TEXT("This Component has been added to a BP Whose base class is not a pawn"));
			return;
		}

	}

	RegisterInitStateFeature();
}

void UPFHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	BindOnActorInitStateChanged(UPFPawnExtensionComponent::Name_ActorFeatureName, FGameplayTag(), false);

	ensure(TryToChangeInitState(FPFGameplayTags::Get().InitState_Spawned));

	CheckDefaultInitialization();
}

void UPFHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	Super::EndPlay(EndPlayReason);
}

void UPFHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();

	//Find ExtComp
	if (Params.FeatureName == UPFPawnExtensionComponent::Name_ActorFeatureName)
	{
		//ExtComp's State = Initialized?
		if (Params.FeatureState == InitTags.InitState_DataInitialized)
		{
			//proceed change state to possible
			CheckDefaultInitialization();
		}
	}
}

bool UPFHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();
	APawn* Pawn = GetPawn<APawn>();
	APFPlayerState* ClonePS = GetPlayerState<APFPlayerState>();

	//Spawned 초기화
	if (!CurrentState.IsValid() && DesiredState == InitTags.InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}

	//Spanwed -> DataAvailable
	if (CurrentState == InitTags.InitState_Spawned && DesiredState == InitTags.InitState_DataAvailable)
	{
		if (!ClonePS)
		{
			return false;
		}

		return true;
	}

	//DataAvailable -> DataInitialized
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		return ClonePS && Manager->HasFeatureReachedInitState(Pawn, UPFPawnExtensionComponent::Name_ActorFeatureName, InitTags.InitState_DataInitialized);
	}

	if (CurrentState == InitTags.InitState_DataInitialized && DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}


	return false;
}

void UPFHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();

	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		APFPlayerState* ClonePS = GetPlayerState<APFPlayerState>();
		if (!ensure(Pawn && ClonePS))
		{
			return;
		}


		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const UPFPawnData* PawnData = nullptr;
		if (UPFPawnExtensionComponent* PawnExtComp = UPFPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<UPFPawnData>();
		}

		//Camera Handling
		if (bIsLocallyControlled && PawnData)
		{
			if (UPFCameraComponent* CameraComponent = UPFCameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
			}
		}

		//Input Handling
		if (APFPlayerController* PFPC = GetController<APFPlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}

	}
}

void UPFHeroComponent::CheckDefaultInitialization()
{
	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();

	static const TArray<FGameplayTag> StateChain = {
		InitTags.InitState_Spawned,
		InitTags.InitState_DataAvailable,
		InitTags.InitState_DataInitialized,
		InitTags.InitState_GameplayReady
	};

	ContinueInitStateChain(StateChain);
}

TSubclassOf<UPFCameraMode> UPFHeroComponent::DetermineCameraMode() const
{
	const APawn* Pawn = GetPawn<APawn>();

	//HeroComponent가 Owner Pawn이 없다면 nullptr
	if (!Pawn)
	{
		return nullptr;
	}

	//HeroComponent's OwnerPawn's ExtComp for Get PawnData
	if (UPFPawnExtensionComponent* PawnExtComp = UPFPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		//for Get DefaultCameraMode of PawnClass
		if (const UPFPawnData* PawnData = PawnExtComp->GetPawnData<UPFPawnData>())
		{
			return PawnData->DefaultCameraMode;
		}

	}

	return nullptr;
}

void UPFHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = Pawn->GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const UPFPawnExtensionComponent* PawnExtComp = UPFPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UPFPawnData* PawnData = PawnExtComp->GetPawnData<UPFPawnData>())
		{
			if (const UPFInputConfig* InputConfig = PawnData->InputConfig)
			{
				const FPFGameplayTags& GameplayTags = FPFGameplayTags::Get();

				for (const FPFMappableConfigPair& Pair : DefaultInputConfigs)
				{
					FModifyContextOptions Options = { };
					Options.bIgnoreAllPressedKeysUntilRelease = false;

					Subsystem->AddPlayerMappableConfig(Pair.Config.LoadSynchronous(), Options);
				}

				UPFEnhancedInputComponent* PFIC = CastChecked<UPFEnhancedInputComponent>(PlayerInputComponent);
				{
					PFIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
					PFIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, false);
				}
				
			}
		}
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), Name_BindInputsNow);
}

void UPFHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		//X : Right, Left
		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);

			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);

			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UPFHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return; 
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();

	//Yaw = Horizontal
	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		double AnimInversionValue = -Value.Y;
		Pawn->AddControllerPitchInput(AnimInversionValue);
	}

}
