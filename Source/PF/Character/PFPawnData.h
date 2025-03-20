// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFPawnData.generated.h"

class UPFCameraMode;
class UPFInputConfig;
/**
 * 
 */
UCLASS()
class PF_API UPFPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPFPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/* Cache for GAS */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PF|Pawn")
	TSubclassOf<APawn> PawnClass;

	/* Camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PF|Camera")
	TSubclassOf<UPFCameraMode> DefaultCameraMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PF|InputConfig")
	TObjectPtr<UPFInputConfig> InputConfig;
};
