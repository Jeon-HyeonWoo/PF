// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFInventoryItemInstance.generated.h"
/**
 * 
 */
class UPFInventoryItemDefinition;

UCLASS()
class PF_API UPFInventoryItemInstance : public UObject
{
	GENERATED_BODY()
	
public:

	UPFInventoryItemInstance(const FObjectInitializer& ObjectIntializer = FObjectInitializer::Get());

public:

	UPROPERTY()
	TSubclassOf<UPFInventoryItemDefinition> ItemDef;
};
