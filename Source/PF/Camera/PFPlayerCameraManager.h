// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "PFPlayerCameraManager.generated.h"

/**
 * 
 */

#define PF_CAMERA_DEFAULT_FOV (80.0f)
#define PF_CAMERA_DEFAULT_PITCH_MIN (-89.0f)
#define PF_CAMERA_DEFAULT_PITCH_MAX (89.0f)
UCLASS()
class PF_API APFPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:

	APFPlayerCameraManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


};
