// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PFMappableConfigPair.generated.h"

/**
 * 
 */

class UPlayerMappableInputConfig;

USTRUCT()
struct FPFMappableConfigPair
{
	GENERATED_BODY()
public:

	FPFMappableConfigPair() = default;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	UPROPERTY(EditAnywhere)
	bool bShouldActivateAutomatically = true;
	
};
