// Fill out your copyright notice in the Description page of Project Settings.


#include "PFInventoryItemInstance.h"
#include "PFInventoryItemDefinition.h"

UPFInventoryItemInstance::UPFInventoryItemInstance(const FObjectInitializer& ObjectIntializer)
	: Super(ObjectIntializer)
{
}

const UPFInventoryItemFragment* UPFInventoryItemInstance::FindFragmentByClass(TSubclassOf<UPFInventoryItemFragment> FragmentClass) const
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UPFInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}

	return nullptr;
}
