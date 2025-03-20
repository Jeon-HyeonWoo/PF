// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "PFInputConfig.generated.h"

class UInputAction;
/**
 * 
 */


USTRUCT(BlueprintType)
struct FPFInputAction
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};

UCLASS()
class PF_API UPFInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPFInputConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FPFInputAction> NatvieInputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))
	TArray<FPFInputAction> AbilityInputActions;


};
