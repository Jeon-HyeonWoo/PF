// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFCharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "PFControllerComponent_CharacterParts.generated.h"

/**
 * 
 */
class UPFPawnComponent_CharacterParts;

USTRUCT()
struct FPFControllerCharacterPartEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FPFCharacterPart Part;

	FPFCharacterPartHandle Handle;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class PF_API UPFControllerComponent_CharacterParts : public UControllerComponent
{
	GENERATED_BODY()
	
public:

	UPFControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPFPawnComponent_CharacterParts* GetPawnCustomizer() const;

	UFUNCTION(BlueprintCallable, Category = Cosmetic)
	void AddCharacterPart(const FPFCharacterPart& NewPart);

	void AddCharacterPartInternal(const FPFCharacterPart& NewPart);

public:

	UPROPERTY(EditAnywhere, Category = Cosmetic)
	TArray<FPFControllerCharacterPartEntry> CharacterParts;
};
