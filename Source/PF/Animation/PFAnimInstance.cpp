// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAnimInstance.h"
#include "AbilitySystemGlobals.h"

void UPFAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeWithAbilitySystem(ASC);
		}
	}
}

void UPFAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC)
{
	/*
	* Connect Ability System Component's GameplayTag with AnimInstance's Property to Delegate
	*/
	GameplayTagPropertyMap.Initialize(this, ASC);
}
