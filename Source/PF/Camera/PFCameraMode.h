// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFCameraMode.generated.h"

/**
 * 
 */

struct FPFCameraModeView
{
	FPFCameraModeView();


	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
	float FieldOfView;
};

UCLASS(Abstract, NotBlueprintable)
class UPFCameraMode : public UObject
{
	GENERATED_BODY()
public:

	UPFCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
		 
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendTime;
	float BlendAlpha;
	float BlendWeight;
};

UCLASS()
class UPFCameraModeStack : public UObject
{
	GENERATED_BODY()
public:

	UPFCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UPFCameraMode* GetCameraModeInstance(TSubclassOf<UPFCameraMode>& CameraModeClass);
	void PushCameraMode(TSubclassOf<UPFCameraMode>& CameraModeClass);
	void EvaluateStack(float DeltaTime, FPFCameraModeView& OutCamreaModeView);
	void UpdateStack(float DeltaTime);
	void BlendStack(FPFCameraModeView& OutCameraModeView) const;
public:

	UPROPERTY()
	TArray<TObjectPtr<UPFCameraMode>> CameraModeInstance;

	UPROPERTY()
	TArray<TObjectPtr<UPFCameraMode>> CameraModeStack;
};
