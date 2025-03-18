// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCameraComponent.h"
#include "PF/Camera/PFCameraMode.h"

UPFCameraComponent::UPFCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), CameraModeStack(nullptr)
{
}

void UPFCameraComponent::OnRegister()
{
	Super::OnRegister();

	if (!CameraModeStack)
	{
		CameraModeStack = NewObject<UPFCameraModeStack>(this);
	}

}

void UPFCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	Super::GetCameraView(DeltaTime, DesiredView);

	UpdateCameraModes();
}

void UPFCameraComponent::UpdateCameraModes()
{
	check(CameraModeStack);

	//Is CameraModeDelegate bind?
	if (DetermineCameraModeDelegate.IsBound())
	{
		//Receive TSubclassOf<CameraMode> from Delegate
		if (const TSubclassOf<UPFCameraMode> CameraMode = DetermineCameraModeDelegate.Execute())
		{
			//CameraModeStack -> PushCameraMode(CameraMode);
		}
	}
}
