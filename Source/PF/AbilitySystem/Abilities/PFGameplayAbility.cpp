// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameplayAbility.h"

UPFGameplayAbility::UPFGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActivationPolicy = EPFAbilityActivationPolicy::OnInputTriggered;
}
