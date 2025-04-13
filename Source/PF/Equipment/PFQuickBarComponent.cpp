// Fill out your copyright notice in the Description page of Project Settings.


#include "PFQuickBarComponent.h"

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
