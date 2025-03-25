// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFUserFacingExperience.generated.h"


class UCommonSession_HostSessionRequest;
/**
 * 
 */
UCLASS()
class PF_API UPFUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, BlueprintPure = false)
	UCommonSession_HostSessionRequest* CreateHostingRequest() const;

public:


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Experience, meta = (AllowedTypes = "PFExperienceDefinition"))
	FPrimaryAssetId ExperienceId;

};
