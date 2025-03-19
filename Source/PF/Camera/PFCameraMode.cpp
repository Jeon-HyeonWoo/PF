// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCameraMode.h"
#include "PFPlayerCameraManager.h"
#include "PFCameraComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PFCameraMode)

FPFCameraModeView::FPFCameraModeView()
	: Location(ForceInit)
	, Rotation(ForceInit)
	, ControlRotation(ForceInit)
	, FieldOfView(PF_CAMERA_DEFAULT_FOV)
{

}

void FPFCameraModeView::Blend(const FPFCameraModeView& Other, float OtherWeight)
{
	if (OtherWeight <= 0.0f)
	{
		return;
	}
	else if (OtherWeight >= 1.0f)
	{
		*this = Other;
		return;
	}

	Location = FMath::Lerp(Location, Other.Location, OtherWeight);

	const FRotator DeltaRotation = (Other.Rotation - Rotation).GetNormalized();
	Rotation = Rotation + (OtherWeight * DeltaRotation);

	const FRotator DeltaControlRotation = (Other.ControlRotation - ControlRotation).GetNormalized();
	ControlRotation = ControlRotation + (OtherWeight * DeltaControlRotation);

	FieldOfView = FMath::Lerp(FieldOfView, Other.FieldOfView, OtherWeight);
}


UPFCameraMode::UPFCameraMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FieldOfView = PF_CAMERA_DEFAULT_FOV;
	ViewPitchMin = PF_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = PF_CAMERA_DEFAULT_PITCH_MAX;

	BlendTime = 0.0f;
	BlendAlpha = 1.0f;
	BlendWeight = 1.0f;

	BlendFunction = EPFCameraModeBlendFunction::EaseOut;
	BlendExponent = 4.0f;
}

void UPFCameraMode::UpdateCameraMode(float DeltaTime)
{
	UpdateView(DeltaTime);

	UpdateBlending(DeltaTime);
}

void UPFCameraMode::UpdateView(float DeltaTime)
{
	FVector PivotLoaction = GetPivotLocation();
	FRotator PivotRotation = GetPivotRotation();

	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	View.Location = PivotLoaction;
	View.Rotation = PivotRotation;

	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;
}

void UPFCameraMode::UpdateBlending(float DeltaTime)
{
	if (BlendTime > 0.0f)
	{
		BlendAlpha += (DeltaTime / BlendTime);
	}
	else
	{
		BlendAlpha = 1.0f;
	}

	const float Exponent = (BlendExponent > 0.0f) ? BlendExponent : 1.0f;
	switch (BlendFunction)
	{
	case EPFCameraModeBlendFunction::Linear:
		BlendWeight = BlendAlpha;
		break;
	case EPFCameraModeBlendFunction::EaseIn:
		BlendWeight = FMath::InterpEaseIn(0.0f, 1.0f, BlendAlpha, Exponent);
		break;
	case EPFCameraModeBlendFunction::EaseOut:
		BlendWeight = FMath::InterpEaseOut(0.0f, 1.0f, BlendAlpha, Exponent);
		break;
	case EPFCameraModeBlendFunction::EaseInOut:
		BlendWeight = FMath::InterpEaseInOut(0.0f, 1.0f, BlendAlpha, Exponent);
		break;
	default:
		checkf(false, TEXT("UpdateBlending : Invalid BlendFunction [%d]\n"), (uint8)BlendFunction);
		break;
	}
}

UPFCameraComponent* UPFCameraMode::GetCloneCameraComponent() const
{
	return CastChecked<UPFCameraComponent>(GetOuter());
}

AActor* UPFCameraMode::GetTargetActor() const
{
	UPFCameraComponent* PFCameraComponent = GetCloneCameraComponent();
	return PFCameraComponent->GetTargetActor();
}

FVector UPFCameraMode::GetPivotLocation() const
{
	const AActor* TargetActor = GetTargetActor();
	check(TargetActor);

	if (const APawn* TargetPawn = Cast<APawn>(TargetActor))
	{
		return TargetPawn->GetPawnViewLocation();
	}

	return FVector();
}

FRotator UPFCameraMode::GetPivotRotation() const
{
	const AActor* TargetActor = GetTargetActor();
	check(TargetActor);

	if (const APawn* TargetPawn = Cast<APawn>(TargetActor))
	{
		return TargetPawn->GetViewRotation(); //Controller's Rotation
	}

	return TargetActor->GetActorRotation();
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

	if ((StackSize > 0) && (CameraModeStack[0] == CameraMode))
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
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
	{
		return;
	}

	int32 RemoveCount = 0;
	int32 RemoveIndex = INDEX_NONE;

	
	for (int32 StackIndex = 0; StackIndex < StackSize; ++StackIndex)
	{
		UPFCameraMode* CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);

		CameraMode->UpdateCameraMode(DeltaTime);

		if (CameraMode->BlendWeight >= 1.0f)
		{
			RemoveIndex = (StackIndex + 1);
			RemoveCount = (StackSize - RemoveIndex);
			break;
		}
	}

	if (RemoveCount > 0)
	{
		CameraModeStack.RemoveAt(RemoveIndex, RemoveCount);
	}
}

void UPFCameraModeStack::BlendStack(FPFCameraModeView& OutCameraModeView) const
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
	{
		return;
	}

	const UPFCameraMode* CameraMode = CameraModeStack[StackSize - 1];
	check(CameraMode);

	OutCameraModeView = CameraMode->View;

	for (int32 StackIndex = (StackSize - 2); StackIndex >= 0; --StackIndex)
	{
		CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);
		OutCameraModeView.Blend(CameraMode->View, CameraMode->BlendWeight);
	}
}

