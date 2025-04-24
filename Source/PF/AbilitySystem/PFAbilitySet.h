// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpec.h"
#include "PFAbilitySet.generated.h"

class UPFGameplayAbility;
class UPFAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FPFAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPFGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;
};

USTRUCT()
struct FPFAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void TakeFromAbilitySystem(UPFAbilitySystemComponent* PFASC);

protected:
	
	/* Allowed GameplayAbilitySpecHandle(int32) */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
};

/**
 * Managed in Pawn Data
 */
UCLASS()
class PF_API UPFAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPFAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	/* Add, Give to Allowed Ability */
	void GiveToAbilitySystem(UPFAbilitySystemComponent* PFASC, FPFAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

public:

	/* Allowed GmaeplayAbilities */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<FPFAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};

/* 
*	Ability's Chracter
*	1. Inherit UObject -> To Managed by Garbage Collection
* 
* 
	Ability's Step.
	1. NonInstanced : CDO	-> Hard to Modify
	2. Instance Per Actor
	3. InstancePerExecution
	-> Degree of Memory
*/