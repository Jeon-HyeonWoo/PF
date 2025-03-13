// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PFGameMode.generated.h"

class UPFExperienceDefinition;
/**
 * 
 */
UCLASS()
class PF_API APFGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	APFGameMode();

	/* Call Immediately After GameModeBase Constrctor was Created */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	/* Call After GameState Constructor was Created */
	virtual void InitGameState() override;

	/* Signals that Player is ready to enter the Game */
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) final;

	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) final;

	/*
	* Select Experience Loading for Next Tick, No Experience to match -> Default
	*/
	void HandleMatchAssignmentIfNotExpectingOne();

	/* Given HandleMatchAssignment's ExperienceId, and ExperienceId Send to ExperienceManager */
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);

	
	/* Get ExperienceManagerComponent's LoadState */
	bool IsExperienceLoaded() const;

	/* Call InitGameState, ExperienceLoad is finished */
	void OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience);
};
