// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPawnExtensionComponent.h"
#include "PF/PFLogChannels.h"
#include "PF/PFGameplayTags.h"
#include "Components/GameFrameworkComponentManager.h"

const FName UPFPawnExtensionComponent::Name_ActorFeatureName("PawnExtension");

UPFPawnExtensionComponent::UPFPawnExtensionComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
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

void UPFPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(PFLog, Error, TEXT("this component has been added to a bp whose base class is not a pawn"));
			return;
		}
	}

	//for Use to GameFrameworkManager's RegisterInitState Step
	RegisterInitStateFeature();


	UGameFrameworkComponentManager* Manager = UGameFrameworkComponentManager::GetForActor(GetOwningActor());
}

void UPFPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	* Delegate
	* Observe Component range : Name_None = All Component,
	* Observe tag state range : receive all tags
	*/
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false); // OnActorInitStateChanged()

	ensure(TryToChangeInitState(FPFGameplayTags::Get().InitState_Spawned));

	//ForceUpdateInitState
	CheckDefaultInitialization();
}

void UPFPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UPFPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	//same if(Registed Other Components)
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
			return false;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		if (bIsLocallyControlled)
		{
			if (!GetController<AController>())
			{
				return false;
			}
		}

		return true;
	}
	
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		/*
		* Pawn에 부착된 모든 Feature들이 InitState의 지점에 도착하면 true를 반환
		*/
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
