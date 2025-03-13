// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFPawnData.generated.h"

/**
 * 
 */
UCLASS()
class PF_API UPFPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPFPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/*  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PF|Pawn")
	TSubclassOf<APawn> PawnClass;
};
