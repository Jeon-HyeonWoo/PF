// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerController.h"
#include "PF/Camera/PFPlayerCameraManager.h"

APFPlayerController::APFPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = APFPlayerCameraManager::StaticClass();
}
