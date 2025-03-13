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

	/*
	* Select Experience Loading for Next Tick
	*/
	void HandleMatchAssignmentIfNotExpectingOne();
	
	/* Call InitGameState, ExperienceLoad is finished */
	void OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience);
};
