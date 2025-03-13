// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PFPlayerState.generated.h"

class UPFExperienceDefinition;
class UPFPawnData;
/**
 * PlayerState is Created after PlayerController 
 */
UCLASS()
class PF_API APFPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	
	virtual void PostInitializeComponents() final;

	/* for cache PawnData, need to know Experience Load is Completed */
	void OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience);

	/* for GAS PawnData Cache */
	UPROPERTY()
	TObjectPtr<const UPFPawnData> PawnData;
	
};
