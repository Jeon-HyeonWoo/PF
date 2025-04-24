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
	/* Input�� trigger �Ǿ��� ��� (Pressed, Released ) */
	OnInputTriggered,
	/* Input�� Held �Ǿ��� ��� */
	WhileInputActive,
	/* Avatar�� �����Ǿ��� ���, ex) Passive Skill */
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
