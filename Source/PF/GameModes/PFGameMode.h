// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PFGameMode.generated.h"

class UPFExperienceDefinition;
class UPFPawnData;
/**
 * 
 */
UCLASS()
class PF_API APFGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	//Constructor and GameMode Override
public:

	APFGameMode();

	/* Call Immediately After GameModeBase Constrctor was Created */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	/* Call After GameState Constructor was Created */
	virtual void InitGameState() override;

	/* Set Default Pawn class -> GameModes PawnClass */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) final;

	/* Signals that Player is ready to enter the Game */
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) final;

	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) final;

	//Request for Experience Load
public:
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

	/* Get Current Loaded Experience PawnData */
	const UPFPawnData* GetPawnDataForController(const AController* InController) const;
};
