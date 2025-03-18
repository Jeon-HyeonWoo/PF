// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCameraMode.h"
#include "PFPlayerCameraManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PFCameraMode)

FPFCameraModeView::FPFCameraModeView()
	: Location(ForceInit)
	, Rotation(ForceInit)
	, ControlRotation(ForceInit)
	, FieldOfView(PF_CAMERA_DEFAULT_FOV)
{

}


UPFCameraMode::UPFCameraMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPFCameraModeStack::UPFCameraModeStack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPFCameraMode* UPFCameraModeStack::GetCameraModeInstance(TSubclassOf<UPFCameraMode>& CameraModeClass)
{

	check(CameraModeClass);

	for (UPFCameraMode* CameraMode : CameraModeInstance)
	{
		if ((CameraMode != nullptr) && (CameraMode->GetClass() == CameraModeClass))
		{
			return CameraMode;
		}
	}

	UPFCameraMode* NewCameraMode = NewObject<UPFCameraMode>(GetOuter(), CameraModeClass, NAME_None, RF_NoFlags);
	check(NewCameraMode);

	CameraModeInstance.Add(NewCameraMode);

	return NewCameraMode;
}

void UPFCameraModeStack::PushCameraMode(TSubclassOf<UPFCameraMode>& CameraModeClass)
{
	if (!CameraModeClass)
	{
		return;
	}

	UPFCameraMode* CameraMode = GetCameraModeInstance(CameraModeClass);
	check(CameraMode);

	int32 StackSize = CameraModeStack.Num();

	if ((StackSize > 0) && (CameraModeStack[0]) == CameraMode)
	{
		return;
	}

	int32 ExistingStackIndex = INDEX_NONE;
	float ExistingStackContribution = 1.0f;

	for (int32 StackIndex = 0; StackIndex < StackSize; ++StackIndex)
	{
		if (CameraModeStack[StackIndex] == CameraMode)
		{
			ExistingStackIndex = StackIndex;
			ExistingStackContribution *= CameraMode->BlendWeight;
			break;
		}
		else
		{
			ExistingStackContribution *= (1.0f - CameraModeStack[StackIndex]->BlendWeight);
		}
	}

	if (ExistingStackIndex != INDEX_NONE)
	{
		CameraModeStack.RemoveAt(ExistingStackIndex);
		StackSize--;
	}
	else 
	{
		ExistingStackContribution = 0.0f;
	}

	const bool bShouldBlend = ((CameraMode->BlendTime > 0.0f) && (StackSize > 0));
	const float BlendWeight = (bShouldBlend ? ExistingStackContribution : 1.0f);
	CameraMode->BlendWeight = BlendWeight;

	CameraModeStack.Insert(CameraMode, 0);

	CameraModeStack.Last()->BlendWeight = 1.0f;
}

void UPFCameraModeStack::EvaluateStack(float DeltaTime, FPFCameraModeView& OutCamreaModeView)
{
	UpdateStack(DeltaTime);

	BlendStack(OutCamreaModeView);
}

void UPFCameraModeStack::UpdateStack(float DeltaTime)
{
}

void UPFCameraModeStack::BlendStack(FPFCameraModeView& OutCameraModeView) const
{
}

