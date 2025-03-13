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

void APFGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	/* Experience is not Loaded, Player can not enter the game */
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
	
}

APawn* APFGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void APFGameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("PFExperienceDefinition"), FName("BP_DefaultExperience"));
	}

	OnMatchAssignmentGiven(ExperienceId);
}

void APFGameMode::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	check(ExperienceId.IsValid());

	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	ExperienceManagerComponent->ServerSetCurrentExperience(ExperienceId);
}

bool APFGameMode::IsExperienceLoaded() const
{
	check(GameState);
	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	
	return ExperienceManagerComponent->IsExperienceLoaded();
}

void APFGameMode::OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience)
{

}
