// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "InputTriggers.h"
#include "InputActionValue.h"
#include "PFInputConfig.h"
#include "PFEnhancedInputComponent.generated.h"

class UPFInputConfig;
/**
 * 
 */
UCLASS()
class PF_API UPFEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	UPFEnhancedInputComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	template <class UserClass, typename FuncType>
	void BindNativeAction(
		const UPFInputConfig* InputConfig,
		const FGameplayTag& InputTag,
		ETriggerEvent TriggerEvent,
		UserClass* Object,
		FuncType Func,
		bool bLogIfNotFound
	);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(
		const UPFInputConfig* InputConfig,
		UserClass* Object,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc,
		TArray<int32>& BindHandles
	);
};

template<class UserClass, typename FuncType>
inline void UPFEnhancedInputComponent::BindNativeAction(const UPFInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);

	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
inline void UPFEnhancedInputComponent::BindAbilityActions(const UPFInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<int32>& BindHandles)
{
	check(InputConfig);

	for (const FPFInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle());
			}
		}
	}
}

