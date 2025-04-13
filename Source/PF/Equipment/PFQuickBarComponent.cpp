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
		* AddDefault�� �Ҵ� ũ���� �ʱ�ȭ�� �ƴ� �߰� �Ҵ�.
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
