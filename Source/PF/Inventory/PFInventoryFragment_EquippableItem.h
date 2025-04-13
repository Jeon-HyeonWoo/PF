// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PFInventoryItemDefinition.h"
#include "Templates/SubClassOf.h"
#include "PFInventoryFragment_EquippableItem.generated.h"

/**
 * 
 */

class UPFEquipmentDefinition;

UCLASS()
class PF_API UPFInventoryFragment_EquippableItem : public UPFInventroyItemFragment
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = PF) 
	TSubclassOf<UPFEquipmentDefinition> EquipmentDefinition;
	
};
