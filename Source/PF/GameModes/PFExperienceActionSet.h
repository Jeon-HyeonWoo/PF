// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFExperienceActionSet.generated.h"


class UGameFeatureAction;
/**
 * 
 */
UCLASS()
class PF_API UPFExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPFExperienceActionSet();

public:

	UPROPERTY(EditAnywhere, Category = "Actions to Perform")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
