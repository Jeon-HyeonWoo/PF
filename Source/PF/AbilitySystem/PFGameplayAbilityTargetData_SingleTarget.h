#pragma once

#include "Abilities/GameplayAbilityTargetTypes.h"
#include "PFGameplayAbilityTargetData_SingleTarget.generated.h"


USTRUCT()
struct FPFGameplayAbilityTargetData_SingleTargetHit : public FGameplayAbilityTargetData_SingleTargetHit
{
	GENERATED_BODY()

public:

	FPFGameplayAbilityTargetData_SingleTargetHit()
		: CartridgeID(-1)
	{}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FPFGameplayAbilityTargetData_SingleTargetHit::StaticStruct();
	}

	UPROPERTY()
	int32 CartridgeID;

};