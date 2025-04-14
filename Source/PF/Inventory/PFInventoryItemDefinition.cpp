// Fill out your copyright notice in the Description page of Project Settings.


#include "PFInventoryItemDefinition.h"

UPFInventoryItemDefinition::UPFInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const UPFInventoryItemFragment* UPFInventoryItemDefinition::FindFragmentByClass(TSubclassOf<UPFInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass)
	{
		for (UPFInventoryItemFragment* Fragment : Fragments)
		{
			/* Is a = 파생 클래스인가? */
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}

	return nullptr;
}
