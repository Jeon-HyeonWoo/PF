// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PF_API UPFGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	/*
	* GmaeInstance's interface
	*/
	virtual void Init() override;
	virtual void Shutdown() override;

	
};
