// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFCharacterPartTypes.h"
#include "PFCosmeticAnimationTypes.h"
#include "Components/PawnComponent.h"
#include "PFPawnComponent_CharacterParts.generated.h"

/**
 * 
 */
class UPFPawnComponent_CharacterParts;

USTRUCT()
struct FPFAppliedCharacterPartEntry
{
	GENERATED_BODY()

	UPROPERTY()
	FPFCharacterPart Part;

	UPROPERTY()
	int32 PartHandle = INDEX_NONE;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> SpawnedComponent = nullptr;
};

USTRUCT(BlueprintType)
struct FPFCharacterPartList
{
	GENERATED_BODY()

public:

	FPFCharacterPartList() : OwnerComponent(nullptr) { }

	FPFCharacterPartList(UPFPawnComponent_CharacterParts* InOwnerComponent) : OwnerComponent(InOwnerComponent) { }

public:

	UPROPERTY()
	TArray<FPFAppliedCharacterPartEntry> Entries;

	UPROPERTY()
	TObjectPtr<UPFPawnComponent_CharacterParts> OwnerComponent;

	int32 PartHandleCount = 0;
};

UCLASS()
class PF_API UPFPawnComponent_CharacterParts : public UPawnComponent
{
	GENERATED_BODY()

public:

	UPFPawnComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPROPERTY()
	FPFCharacterPartList CharacterPartList;

	UPROPERTY(EditAnywhere, Category = Cosmetics)
	FPFAnimBodyStyleSelectionSet BodyMeshes;

};
