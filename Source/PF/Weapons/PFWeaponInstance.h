// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PF/Cosmetics/PFCosmeticAnimationTypes.h"
#include "PF/Equipment/PFEquipmentInstance.h"
#include "PFWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class PF_API UPFWeaponInstance : public UPFEquipmentInstance
{
	GENERATED_BODY()
	
public:

	UPFWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FPFAnimLayerSelectionSet EquippedAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FPFAnimLayerSelectionSet UnequippedAnimSet;
};
