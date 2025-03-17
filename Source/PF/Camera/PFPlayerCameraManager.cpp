// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerCameraManager.h"

APFPlayerCameraManager::APFPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultFOV = PF_CAMERA_DEFAULT_FOV;
	ViewPitchMin = PF_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = PF_CAMERA_DEFAULT_PITCH_MAX;
}
