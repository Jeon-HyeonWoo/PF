// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCameraMode_ThirdPerson.h"
#include "Curves/CurveVector.h"
#include "Curves/RichCurve.h"

UPFCameraMode_ThirdPerson::UPFCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	
	/*TargetOffSetCurveNative = CreateDefaultSubobject<UCurveVector>(TEXT("TargetOffSetCurveNative"));
	check(TargetOffSetCurveNative);

	TargetOffSetCurveNative->FloatCurves[0].AddKey(-90.0f, -375.0f);
	TargetOffSetCurveNative->FloatCurves[0].AddKey(90.0f, -250.0f);
	TargetOffSetCurveNative->FloatCurves[0].AddKey(-40.0f, -325.0f);

	TargetOffSetCurveNative->FloatCurves[1].AddKey(-90.0f, 60.0f);

	TargetOffSetCurveNative->FloatCurves[2].AddKey(-90.0f, 60.0f);
	TargetOffSetCurveNative->FloatCurves[2].AddKey(0.0f, -10.0f);

	for (auto& Key : TargetOffSetCurveNative->FloatCurves[0].Keys)
	{
		Key.InterpMode = ERichCurveInterpMode::RCIM_Cubic;
	}

	for (auto& Key : TargetOffSetCurveNative->FloatCurves[1].Keys)
	{
		Key.InterpMode = ERichCurveInterpMode::RCIM_Cubic;
	}

	for (auto& Key : TargetOffSetCurveNative->FloatCurves[2].Keys)
	{
		Key.InterpMode = ERichCurveInterpMode::RCIM_Cubic;
	}*/
}

void UPFCameraMode_ThirdPerson::UpdateView(float DeltaTime)
{
	FVector PivotLocation = GetPivotLocation();
	FRotator PivotRotation = GetPivotRotation();

	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;

	if (TargetOffSetCurve)
	{
		const FVector TargetOffset = TargetOffSetCurve->GetVectorValue(PivotRotation.Pitch);
		View.Location = PivotLocation + PivotRotation.RotateVector(TargetOffset);
	}
}
