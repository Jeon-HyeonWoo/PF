// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFCameraMode.generated.h"

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class UPFCameraMode : public UObject
{
	GENERATED_BODY()
public:

	UPFCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

UCLASS()
class UPFCameraModeStack : public UObject
{
	GENERATED_BODY()
public:

	UPFCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	TArray<TObjectPtr<UPFCameraMode>> CameraModeInstance;

	UPROPERTY()
	TArray<TObjectPtr<UPFCameraMode>> CameraModeStack;
};
