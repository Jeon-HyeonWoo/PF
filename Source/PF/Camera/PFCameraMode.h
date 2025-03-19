// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PFCameraMode.generated.h"

class UPFCameraComponent;
/**
 * 
 */

UENUM(BlueprintType)
enum class EPFCameraModeBlendFunction : uint8
{
	Linear,		
	EaseIn,		
	EaseOut,	
	EaseInOut,	
	COUNT
};

struct FPFCameraModeView
{
	FPFCameraModeView();

	void Blend(const FPFCameraModeView& Other, float OtherWeight);

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

	void UpdateCameraMode(float DeltaTime);
	virtual void UpdateView(float DeltaTime);
	void UpdateBlending(float DeltaTime);

public:
		 
	UPFCameraComponent* GetCloneCameraComponent() const;
	AActor* GetTargetActor() const;
	FVector GetPivotLocation() const;
	FRotator GetPivotRotation() const;

	FPFCameraModeView View;

	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "5.0", UIMax = "170", ClampMin = "5.0", ClampMax = "170.0"))
	float FieldOfView;

	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.0", ClampMax = "89.9"))
	float ViewPitchMin;

	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMax;

	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendTime;
	float BlendAlpha;
	float BlendWeight;

	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendExponent;

	EPFCameraModeBlendFunction BlendFunction;
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
