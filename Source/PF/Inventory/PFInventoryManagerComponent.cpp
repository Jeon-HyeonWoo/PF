// Fill out your copyright notice in the Description page of Project Settings.


#include "PFInventoryManagerComponent.h"

UPFInventoryManagerComponent::UPFInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{
}
