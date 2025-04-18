// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PFGameState.generated.h"

class UPFExperienceManagerComponent;
/**
 * 
 */
UCLASS()
class PF_API APFGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	APFGameState();

public:

	UPROPERTY()
	TObjectPtr<UPFExperienceManagerComponent> ExperienceManagerComponent;
	
};
