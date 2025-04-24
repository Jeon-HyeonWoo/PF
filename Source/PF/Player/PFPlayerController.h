// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ModularPlayerController.h"
#include "PFPlayerController.generated.h"

/**
 * 
 */

class APFPlayerState;
class UPFAbilitySystemComponent;

UCLASS()
class PF_API APFPlayerController : public AModularPlayerController
{
	GENERATED_BODY()

public:

	APFPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/* Merge broken input processing */
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

public: 

	APFPlayerState* GetPFPlayerState() const;
	UPFAbilitySystemComponent* GetPFAbilitySystemComponent() const;

};
