// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerState.h"
#include "PF/GameModes/PFExperienceManagerComponent.h"
#include "PF/GameModes/PFGameMode.h"

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
}
