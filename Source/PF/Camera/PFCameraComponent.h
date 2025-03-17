// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PFCameraComponent.generated.h"

class UPFCameraModeStack;
/**
 * 
 */
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

public:

	UPROPERTY() 
	TObjectPtr<UPFCameraModeStack> CameraModeStack;
};
