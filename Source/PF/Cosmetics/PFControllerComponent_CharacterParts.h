// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFCharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "PFControllerComponent_CharacterParts.generated.h"

/**
 * 
 */

USTRUCT()
struct FPFControllerCharacterPartEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FPFCharacterPart Part;

	FPFCharacterPartHandle Handle;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class PF_API UPControllerComponent_CharacterParts : public UControllerComponent
{
	GENERATED_BODY()
	
public:

	UPControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPROPERTY(EditAnywhere, Category = Cosmetic)
	TArray<FPFControllerCharacterPartEntry> CaracterParts;
};
