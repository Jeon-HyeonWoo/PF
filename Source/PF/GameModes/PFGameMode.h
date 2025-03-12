// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PFGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PF_API APFGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	APFGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/*
	* Select Experience Loading for Next Tick
	*/
	void HandleMatchAssignmentIfNotExpectingOne();
};
