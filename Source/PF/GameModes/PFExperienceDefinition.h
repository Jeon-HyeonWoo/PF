// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFExperienceDefinition.generated.h"

class UPFPawnData;
class UPFExperienceActionSet;
class UGameFeatureAction;
/**
 * 
 */
UCLASS()
class PF_API UPFExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPFExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<UPFPawnData> DefaultPawnData;

public:
	//GameFeatures

	/* Which GameFeature to Activate */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<FString> GameFeaturesToEnable;

	/* Which GameFeature Action to Activate */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<TObjectPtr<UPFExperienceActionSet>> ActionSets;
	
	/*  */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
