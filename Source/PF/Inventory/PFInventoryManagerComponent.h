// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PFInventoryManagerComponent.generated.h"


class UPFInventoryItemInstance;
class UPFInventoryItemDefinition;

USTRUCT(BlueprintType)
struct FPFInventoryEntry 
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UPFInventoryItemInstance> Instance = nullptr;
};

USTRUCT(BlueprintType)
struct FPFInventoryList
{
	GENERATED_BODY()

	FPFInventoryList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{

	}

	UPFInventoryItemInstance* AddEntry(TSubclassOf<UPFInventoryItemDefinition> ItemDef);

	UPROPERTY()
	TArray<FPFInventoryEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};


/*
* Attach to Controller
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_API UPFInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPFInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UFUNCTION(BlueprintCallable, Category = Inventory)
	UPFInventoryItemInstance* AddItemDefinition(TSubclassOf<UPFInventoryItemDefinition> ItemDef);

public:

	UPROPERTY()
	FPFInventoryList InventoryList;

		
};
