// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerState.h"
#include "PF/GameModes/PFExperienceManagerComponent.h"

void APFPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->GetComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void APFPlayerState::OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience)
{
}
