// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFEquipmentDefinition.h"
#include "PFEquipmentInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PF_API UPFEquipmentInstance : public UObject
{
	GENERATED_BODY()

public:

	UPFEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnEquipped"))
	void K2_OnEquipped();

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnUnEquipped"))
	void K2_OnUnEquipped();

	UFUNCTION(BlueprintPure, Category = Equipment)
	TArray<AActor*> GetSpawnedActors() const { return SpawnedActors; }

	UFUNCTION(BlueprintPure, Category = Equipment)
	APawn* GetPawn() const;

	virtual void OnEquipped();
	virtual void OnUnEquipped();

public:

	void SpawnEquipmentActors(const TArray<FPFEquipmentActorToSpawn>& ActorsToSpawn);
	void DestroyEquipmentActors(); 

	/* Redirect OutputType Pawn* -> Want to Type */
	UFUNCTION(BlueprintPure, Category = Equipment, meta = (DeterminesOutputType = PawnType))
	APawn* GetTypedPawn(TSubclassOf<APawn> PawnType) const;

public:

	UPROPERTY()
	TObjectPtr<UObject> Instigator;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;
};
