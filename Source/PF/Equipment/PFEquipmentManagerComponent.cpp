// Fill out your copyright notice in the Description page of Project Settings.


#include "PFEquipmentManagerComponent.h"
#include "PFEquipmentInstance.h"
#include "PFEquipmentDefinition.h"

UPFEquipmentManagerComponent::UPFEquipmentManagerComponent(const FObjectInitializer& ObjectIntializer)
	: Super(ObjectIntializer)
	, EquipmentList(this)
{
}

UPFEquipmentInstance* FPFEquipmentList::AddEntry(TSubclassOf<UPFEquipmentDefinition> EquipmentDefinition)
{
	
	UPFEquipmentInstance* Result = nullptr;
	check(EquipmentDefinition != nullptr);
	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());

	const UPFEquipmentDefinition* EquipmentCDO = GetDefault<UPFEquipmentDefinition>(EquipmentDefinition);

	TSubclassOf<UPFEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;

	if (!InstanceType)
	{
		InstanceType = UPFEquipmentInstance::StaticClass();
	}

	FPFAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.EquipmentDefinition = EquipmentDefinition;
	NewEntry.Instance = NewObject<UPFEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType);
	Result = NewEntry.Instance;

	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);

	return Result;
}

void FPFEquipmentList::RemoveEntry(UPFEquipmentInstance* EquipmentInstance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FPFAppliedEquipmentEntry& Entry = *EntryIt;

		if (Entry.Instance == EquipmentInstance)
		{
			EquipmentInstance->DestroyEquipmentActors();
			EntryIt.RemoveCurrent();
		}
	}
}

UPFEquipmentInstance* UPFEquipmentManagerComponent::EquipItem(TSubclassOf<UPFEquipmentDefinition> EquipmentDefinition)
{
	UPFEquipmentInstance* Result = nullptr;

	if (EquipmentDefinition)
	{
		Result = EquipmentList.AddEntry(EquipmentDefinition);
		if (Result)
		{
			Result->OnEquipped();
		}
	}

	return Result;
}

void UPFEquipmentManagerComponent::UnEquipItem(UPFEquipmentInstance* ItemInstance)
{
	if (ItemInstance)
	{
		ItemInstance->OnUnEquipped();

		EquipmentList.RemoveEntry(ItemInstance);
	}
}


