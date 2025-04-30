// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "PFAnimInstance.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;

UCLASS()
class PF_API UPFAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	
	void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);

public:

	UPROPERTY(BlueprintReadOnly, Category = "Character State Data")
	float GroundDistance = -1.0f;

	/* GameplayTag와 AnimInstance의 속성값 매핑 */
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
