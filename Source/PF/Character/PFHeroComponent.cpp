// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHeroComponent.h"
#include "PF/PFLogChannels.h"
#include "PF/PFGameplayTags.h"
#include "PF/Character/PFPawnExtensionComponent.h"
#include "PF/Character/PFPawnData.h"
#include "PF/Player/PFPlayerState.h"
#include "Components/GameFrameworkComponentManager.h"


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
		if (!GetPawn<APawn>())
		{
			UE_LOG(PFLog, Error, TEXT("this component has been added to a bp whoes base class is not a pawn"));
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

	if (Params.FeatureName == UPFPawnExtensionComponent::Name_ActorFeatureName)
	{
		if (Params.FeatureState == InitTags.InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

bool UPFHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	const FPFGameplayTags& InitTags = FPFGameplayTags::Get();
	APawn* Pawn = GetPawn<APawn>();
	APlayerState* PFPS = GetPlayerState<APlayerState>();

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
		if (!PFPS)
		{
			return false;
		}

		return true;
	}
	
	//DataAvailable -> DataInitialized
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		/*
			PawnExtComp가 DataInitailized일 때 승인
			Pawn에 있는, ExtComponent::Name이, InitState_Step일때 InitState를 진행.
			함수이름대로 1. Pawn 가지고 있는 2. Feature(Component)가 3.InitState에 도달했다면,
		*/
		return PFPS && Manager->HasFeatureReachedInitState(Pawn, UPFPawnExtensionComponent::Name_ActorFeatureName, InitTags.InitState_DataInitialized);
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
		APFPlayerState* PFPS = GetPlayerState<APFPlayerState>();
		if (!ensure(Pawn && PFPS))
		{
			return;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const UPFPawnData* PawnData = nullptr;
		if (UPFPawnExtensionComponent* PawnExtComp = UPFPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<UPFPawnData>();
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
