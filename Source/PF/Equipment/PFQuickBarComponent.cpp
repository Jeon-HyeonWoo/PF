// Fill out your copyright notice in the Description page of Project Settings.


#include "PFQuickBarComponent.h"
#include "PFEquipmentDefinition.h"
#include "PFEquipmentInstance.h"
#include "../Equipment/PFEquipmentManagerComponent.h"
#include "../Inventory/PFInventoryFragment_EquippableItem.h"
#include "../Inventory/PFInventoryItemInstance.h"


UPFQuickBarComponent::UPFQuickBarComponent(const FObjectInitializer& ObjectIntializer)
	: Super(ObjectIntializer)
{
}

void UPFQuickBarComponent::BeginPlay()
{
	if (Slots.Num() < NumSlots)
	{
		/*
		* AddDefault는 할당 크기의 초기화가 아닌 추가 할당.
		*/
		Slots.AddDefaulted(NumSlots - Slots.Num());
	}

	Super::BeginPlay();
}

UPFEquipmentManagerComponent* UPFQuickBarComponent::FindEquipmentManager() const
{
	if (AController* OwnerComponent = Cast<AController>(GetOwner()))
	{
		if (APawn* Pawn = OwnerComponent->GetPawn())
		{
			return Pawn->FindComponentByClass<UPFEquipmentManagerComponent>();
		}
	}

	return nullptr;
}

void UPFQuickBarComponent::UnEquipItemInSlot()
{
	if (UPFEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
	{
		if (EquippedItem)
		{
			EquipmentManager->UnEquipItem(EquippedItem);

			EquippedItem = nullptr;
		}
	}
}

void UPFQuickBarComponent::EquipItemInSlot()
{
	check(Slots.IsValidIndex(ActiveSlotIndex));
	check(EquippedItem == nullptr);

	if (UPFInventoryItemInstance* SlotItem = Slots[ActiveSlotIndex])
	{
		if (const UPFInventoryFragment_EquippableItem* EquipInfo = SlotItem->FindFragmentByClass<UPFInventoryFragment_EquippableItem>())
		{
			TSubclassOf<UPFEquipmentDefinition> EquipDef = EquipInfo->EquipmentDefinition;
			if (EquipDef)
			{
				if (UPFEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
				{
					EquippedItem = EquipmentManager->EquipItem(EquipDef);
					if (EquippedItem)
					{
						EquippedItem->Instigator = SlotItem;
					}
				}
			}
		}
	}
}

void UPFQuickBarComponent::AddItemSlot(int32 SlotIndex, UPFInventoryItemInstance* Item)
{
	if (Slots.IsValidIndex(SlotIndex) && (Item != nullptr))
	{
		if (Slots[SlotIndex] == nullptr)
		{
			Slots[SlotIndex] = Item;
		}
	}
}

void UPFQuickBarComponent::SetActiveSlotIndex(int32 NewIndex)
{
	if (Slots.IsValidIndex(NewIndex) && (ActiveSlotIndex != NewIndex))
	{
		UnEquipItemInSlot();
		ActiveSlotIndex = NewIndex;
		EquipItemInSlot();
			
	}
}
