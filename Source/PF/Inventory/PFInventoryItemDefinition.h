// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFInventoryItemDefinition.generated.h"



/*
* 
*/
UCLASS(Abstract,DefaultToInstanced, EditInlineNew)
class UPFInventoryItemFragment : public UObject
{
	GENERATED_BODY()

public: 

};

UCLASS(Blueprintable)
class PF_API UPFInventoryItemDefinition : public UObject
{
	GENERATED_BODY()
	
public:

	UPFInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	const UPFInventoryItemFragment* FindFragmentByClass(TSubclassOf<UPFInventoryItemFragment> FragmentClass) const;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Display)
	TArray<TObjectPtr<UPFInventoryItemFragment>> Fragments;
};
