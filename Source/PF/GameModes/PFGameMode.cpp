// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameMode.h"
#include "PFGameState.h"
#include "PF/Player/PFPlayerController.h"
#include "PF/Player/PFPlayerState.h"
#include "PF/Character/PFCharacter.h"
#include "PF/GameModes/PFExperienceManagerComponent.h"
#include "PF/GameModes/PFExperienceDefinition.h"

APFGameMode::APFGameMode()
{
	GameStateClass = APFGameState::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();
	PlayerStateClass = APFPlayerState::StaticClass();
	DefaultPawnClass = APFCharacter::StaticClass();
}

void APFGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void APFGameMode::InitGameState()
{
	Super::InitGameState();

	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void APFGameMode::HandleMatchAssignmentIfNotExpectingOne()
{
}

void APFGameMode::OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience)
{

}
