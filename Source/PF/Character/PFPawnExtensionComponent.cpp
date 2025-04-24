// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPawnExtensionComponent.h"
#include "PF/PFLogChannels.h"
#include "PF/PFGameplayTags.h"
#include "Components/GameFrameworkComponentManager.h"
#include "PF/AbilitySystem/PFAbilitySystemComponent.h"

const FName UPFPawnExtensionComponent::Name_ActorFeatureName("PawnExtension");

UPFPawnExtensionComponent::UPFPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UPFPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetPawn<APawn>())
	{
		UE_LOG(PFLog, Error, TEXT("this Component has been added to a BP Whose base class is not a Pawn!"));
		return;
	}

	RegisterInitStateFeature();

	UGameFrameworkComponentManager* Manager = UGameFrameworkComponentManager::GetForActor(GetOwningActor());
}

void UPFPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

	ensure(TryToChangeInitState(FPFGameplayTags::Get().InitState_Spawned));

	CheckDefaultInitialization();
}

void UPFPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	Super::EndPlay(EndPlayReason);
}

void UPFPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName != Name_ActorFeatureName)
	{
		const FPFGameplayTags& InitTags = FPFGameplayTags::Get();
		if (Params.FeatureState == InitTags.InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

bool UPFPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();

	if (!CurrentState.IsValid() && DesiredState == InitTags.InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}

	if (CurrentState == InitTags.InitState_Spawned && DesiredState == InitTags.InitState_DataAvailable)
	{
		if (!PawnData)
		{
			UE_LOG(PFLog, Error, TEXT("PawnData is not set!"));
			return false;
		}
		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		if (bIsLocallyControlled)
		{
			if (!GetController<AController>())
			{
				UE_LOG(PFLog, Error, TEXT("Pawn has no Controller!"));
				return false;
			}
		}

		return true;
	}

	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		UE_LOG(PFLog, Log, TEXT("CanChangeInitState: %s -> %s"), *CurrentState.ToString(), *DesiredState.ToString());
		return Manager->HaveAllFeaturesReachedInitState(Pawn, InitTags.InitState_DataAvailable);
	}

	if (CurrentState == InitTags.InitState_DataInitialized && DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}


	return false;
}

void UPFPawnExtensionComponent::CheckDefaultInitialization()
{
	CheckDefaultInitializationForImplementers();

	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();

	static const TArray<FGameplayTag> StateChain = {
		InitTags.InitState_Spawned,
		InitTags.InitState_DataAvailable,
		InitTags.InitState_DataInitialized,
		InitTags.InitState_GameplayReady
	};

	ContinueInitStateChain(StateChain);
}

void UPFPawnExtensionComponent::SetPawnData(const UPFPawnData* InPawnData)
{
	APawn* Pawn = GetPawnChecked<APawn>();

	if (Pawn->GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		return;
	}

	PawnData = InPawnData;
}

void UPFPawnExtensionComponent::SetupPlayerInputComponent()
{
	CheckDefaultInitialization();
}


void UPFPawnExtensionComponent::InitialzeAbilitySystem(UPFAbilitySystemComponent* InASC, AActor* InOwnerActor)
{
	check(InASC && InOwnerActor);

	/* Cached ASC == Param's ASC -> Return */
	if (AbilitySystemComponent == InASC)
	{
		return;
	}

	/* Changed Ability System -> Current ACS UnInit */
	if (AbilitySystemComponent)
	{
		UnInitializeAbilitySystem();
	}

	/* PawnExtensionComponent's OwnerPawn = User Pawn */
	APawn* Pawn = GetPawnChecked<APawn>();
	AActor* ExistingAvatar = InASC->GetAvatarActor();
	check(!ExistingAvatar);
	
	/* Resetting AbilitySystem OwnerActor and AvatarActor */
	AbilitySystemComponent = InASC;
	AbilitySystemComponent->InitAbilityActorInfo(InOwnerActor, Pawn);
 }

void UPFPawnExtensionComponent::UnInitializeAbilitySystem()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
	AbilitySystemComponent = nullptr;
}
