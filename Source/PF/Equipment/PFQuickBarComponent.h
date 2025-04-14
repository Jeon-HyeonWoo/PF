// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "PFQuickBarComponent.generated.h"

/**
 * 
 */

class UPFEquipmentManagerComponent;
class UPFInventoryItemInstance;
class UPFEquipmentInstance;

UCLASS()
class PF_API UPFQuickBarComponent : public UControllerComponent
{
	GENERATED_BODY()

public:

	UPFQuickBarComponent(const FObjectInitializer& ObjectIntializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

public:

	UPFEquipmentManagerComponent* FindEquipmentManager() const;
	void UnEquipItemInSlot();
	void EquipItemInSlot();

	UFUNCTION(BlueprintCallable)
	void AddItemSlot(int32 SlotIndex, UPFInventoryItemInstance* Item);

	UFUNCTION(BlueprintCallable, Category = "PF")
	void SetActiveSlotIndex(int32 NewIndex);

public:

	/* QuickBar Default Slot Number */
	UPROPERTY()
	int32 NumSlots = 3;
	
	/* QuickBar Slot List */
	UPROPERTY()
	TArray<TObjectPtr<UPFInventoryItemInstance>> Slots;

	/* Active Slot Index, Maximum Range = Num Slots */
	UPROPERTY()
	int32 ActiveSlotIndex = -1;

	/* Cached Current Equipment Info */
	UPROPERTY()
	TObjectPtr<UPFEquipmentInstance> EquippedItem;
};
