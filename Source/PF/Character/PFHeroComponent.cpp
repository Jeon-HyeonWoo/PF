// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHeroComponent.h"
#include "PF/PFLogChannels.h"
#include "PF/PFGameplayTags.h"
#include "PF/Character/PFPawnExtensionComponent.h"

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
}

bool UPFHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	return false;
}

void UPFHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
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
