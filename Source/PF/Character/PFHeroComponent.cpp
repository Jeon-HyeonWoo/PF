// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHeroComponent.h"
#include "PF/PFLogChannels.h"
#include "PF/PFGameplayTags.h"
#include "PF/Character/PFPawnExtensionComponent.h"
#include "PF/Character/PFPawnData.h"
#include "PF/Player/PFPlayerState.h"
#include "Components/GameFrameworkComponentManager.h"
#include "PF/Camera/PFCameraMode.h"
#include "PF/Camera/PFCameraComponent.h"

const FName UPFHeroComponent::Name_ActorFeatureName("HeroComponent");

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

		if (!GetPawn<APawn>()) // OwnerPawn�� �������� �ʴ´ٸ�,
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

	//Spawned �ʱ�ȭ
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

	//HeroComponent�� Owner Pawn�� ���ٸ� nullptr
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