// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ModularPlayerController.h"
#include "PFPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PF_API APFPlayerController : public AModularPlayerController
{
	GENERATED_BODY()

public:

	APFPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
