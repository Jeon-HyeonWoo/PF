// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "PF/AbilitySystem/PFAbilitySet.h"
#include "PFEquipmentManagerComponent.generated.h"

/**
 * 
 */
class UPFEquipmentDefinition;
class UPFEquipmentInstance;

USTRUCT(BlueprintType)
struct FPFAppliedEquipmentEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<UPFEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	TObjectPtr<UPFEquipmentInstance> Instance = nullptr;

	UPROPERTY()
	FPFAbilitySet_GrantedHandles GrantedHandles;
};

USTRUCT(BlueprintType)
struct FPFEquipmentList
{
	GENERATED_BODY()

	FPFEquipmentList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{

	}

	UPFEquipmentInstance* AddEntry(TSubclassOf<UPFEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(UPFEquipmentInstance* EquipmentInstance);

	UPFAbilitySystemComponent* GetAbilitySystemComponent() const;

	UPROPERTY()
	TArray<FPFAppliedEquipmentEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

UCLASS()
class PF_API UPFEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()
	
public:

	UPFEquipmentManagerComponent(const FObjectInitializer& ObjectIntializer = FObjectInitializer::Get());

public: 

	UPFEquipmentInstance* EquipItem(TSubclassOf<UPFEquipmentDefinition> EquipmentDefinition);
	void UnEquipItem(UPFEquipmentInstance* ItemInstance);

public:

	UPROPERTY()
	FPFEquipmentList EquipmentList;
};
