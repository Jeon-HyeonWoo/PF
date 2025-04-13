// Fill out your copyright notice in the Description page of Project Settings.


#include "PFInventoryManagerComponent.h"
#include "PFInventoryItemInstance.h"
#include "PFInventoryItemDefinition.h"

UPFInventoryItemInstance* FPFInventoryList::AddEntry(TSubclassOf<UPFInventoryItemDefinition> ItemDef)
{
	UPFInventoryItemInstance* Result = nullptr;

	check(ItemDef); 
	check(OwnerComponent);

	/* OwnerComponent = ManagerComponent, ManagerComponent's onwer = controller */
	AActor* OwningActor = OwnerComponent->GetOwner(); 
	check(OwningActor->HasAuthority());

	FPFInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UPFInventoryItemInstance>(OwningActor);
	NewEntry.Instance->ItemDef = ItemDef;

	Result = NewEntry.Instance;

	return Result;
}


UPFInventoryManagerComponent::UPFInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{
}

UPFInventoryItemInstance* UPFInventoryManagerComponent::AddItemDefinition(TSubclassOf<UPFInventoryItemDefinition> ItemDef)
{
	UPFInventoryItemInstance* Result = nullptr;

	if (ItemDef)
	{
		Result = InventoryList.AddEntry(ItemDef);
	}

	return Result;
}

