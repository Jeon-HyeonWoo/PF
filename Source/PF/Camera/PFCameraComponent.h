// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PFCameraComponent.generated.h"

class UPFCameraModeStack;
class UPFCameraMode;

template <class TClass> class TSubclassOf;

/* (Return Type, Delegate_name) */
DECLARE_DELEGATE_RetVal(TSubclassOf<UPFCameraMode>, FPFCameraModeDelegate)

UCLASS()
class PF_API UPFCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:

	UPFCameraComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	/*
	* CameraCompoent Interface
	*/
	virtual void OnRegister() final;
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) final;

public:

	static UPFCameraComponent* FindCameraComponent(const AActor* Actor)
	{
		return (Actor ? Actor->FindComponentByClass<UPFCameraComponent>() : nullptr);
	}
	AActor* GetTargetActor() const { return GetOwner(); }
	void UpdateCameraModes();

public:

	UPROPERTY() 
	TObjectPtr<UPFCameraModeStack> CameraModeStack;

	/* Get Current CameraMode Delegate */
	FPFCameraModeDelegate DetermineCameraModeDelegate;
};
