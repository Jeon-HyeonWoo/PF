// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFUserFacingExperience.generated.h"

/**
 * 
 */
UCLASS()
class PF_API UPFUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "PFExperienceDefinition"))
	FPrimaryAssetId ExperienceId;

};
