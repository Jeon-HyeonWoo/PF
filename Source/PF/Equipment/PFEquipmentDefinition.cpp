// Fill out your copyright notice in the Description page of Project Settings.


#include "PFEquipmentDefinition.h"
#include "PFEquipmentInstance.h"

UPFEquipmentDefinition::UPFEquipmentDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstanceType = UPFEquipmentInstance::StaticClass();
}
