// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAbilitySet.h"
#include "PFAbilitySystemComponent.h"
#include "Abilities/PFGameplayAbility.h"


void FPFAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FPFAbilitySet_GrantedHandles::TakeFromAbilitySystem(UPFAbilitySystemComponent* PFASC)
{
	/* Owner check */
	if (!PFASC->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			PFASC->ClearAbility(Handle);
		}
	}
}


UPFAbilitySet::UPFAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPFAbilitySet::GiveToAbilitySystem(UPFAbilitySystemComponent* PFASC, FPFAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	/* 1. GetAbilitySystemComponent */
	check(PFASC);

	/* 2. Authority check */
	if (!PFASC->IsOwnerActorAuthoritative())
	{
		return;
	}

	/* 3. Travel in GrantedAbilities */
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FPFAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];
		/* 3-1. Ability Valid check */
		if (!IsValid(AbilityToGrant.Ability))
		{
			continue;
		}

		

		/* 3-2. Get Ability Default Object to Array */
		UPFGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UPFGameplayAbility>();

		/* 3-3. Match to Ability source and tags */
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		/* 3-4. Give Ability to form of Spec */
		const FGameplayAbilitySpecHandle AbilitySpecHandle = PFASC->GiveAbility(AbilitySpec);
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}

	
}

