// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFCharacterPartTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPFCharacterPartHandle
{
	GENERATED_BODY()

	void Reset()
	{
		PartHandle = INDEX_NONE;
	}

	bool IsValid() const
	{
		return PartHandle != INDEX_NONE;
	}

	UPROPERTY()
	int32 PartHandle = INDEX_NONE;

};

USTRUCT(BlueprintType)
struct FPFCharacterPart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PartClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

};