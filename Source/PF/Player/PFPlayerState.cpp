// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerState.h"

/* GameMode and Experience */
#include "PF/GameModes/PFExperienceManagerComponent.h"
#include "PF/GameModes/PFGameMode.h"
/* AbilitySystem */
#include "PF/AbilitySystem/PFAbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PF/AbilitySystem/PFAbilitySet.h"
#include "PF/Character/PFPawnData.h"

APFPlayerState::APFPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Ability System Component Create */
	{
		AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UPFAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	}
}

void APFPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/* Set AbilitySystem Owenr Actor, Use Ability Actor */
	check(AbilitySystemComponent);
	{
		FGameplayAbilityActorInfo* ActorInfo = AbilitySystemComponent->AbilityActorInfo.Get();
		check(ActorInfo->OwnerActor == this);
		check(ActorInfo->OwnerActor == ActorInfo->AvatarActor);
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());


	/* Setting Pawn Data */
	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->GetComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void APFPlayerState::OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience)
{
	if (APFGameMode* GameMode = GetWorld()->GetAuthGameMode<APFGameMode>())
	{
		const UPFPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

void APFPlayerState::SetPawnData(const UPFPawnData* InPawnData)
{
	check(InPawnData);

	check(!PawnData);

	PawnData = InPawnData;

	for (UPFAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}
}
