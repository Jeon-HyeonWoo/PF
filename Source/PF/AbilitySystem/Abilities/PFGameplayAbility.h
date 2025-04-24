// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PFGameplayAbility.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPFAbilityActivationPolicy : uint8
{
	/* Input이 trigger 되었을 경우 (Pressed, Released ) */
	OnInputTriggered,
	/* Input이 Held 되었을 경우 */
	WhileInputActive,
	/* Avatar가 생성되었을 경우, ex) Passive Skill */
	OnSpawn,
};

UCLASS()
class PF_API UPFGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public: 

	UPFGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PF|AbilityActivation")
	EPFAbilityActivationPolicy ActivationPolicy;
};
