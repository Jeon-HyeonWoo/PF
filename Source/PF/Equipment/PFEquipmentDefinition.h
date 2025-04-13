// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFEquipmentDefinition.generated.h"

/**
 * 
 */

class UPFEquipmentInstance;

USTRUCT()
struct FPFEquipmentActorToSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = Equipment)
	FName AttackSocket;

	UPROPERTY(EditAnywhere, Category = Equipment)
	FTransform AttachTransform;
};

UCLASS(Blueprintable)
class PF_API UPFEquipmentDefinition : public UObject
{
	GENERATED_BODY()
	
public:

	UPFEquipmentDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPROPERTY(EditDefaultsOnly, Category = Equipment)
	TSubclassOf<UPFEquipmentInstance> InstanceType;

	UPROPERTY(EditDefaultsOnly, Category = Equipment)
	TArray<FPFEquipmentActorToSpawn> ActorToSpawn;
};
