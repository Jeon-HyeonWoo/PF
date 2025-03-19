// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFCameraMode.h"
#include "PFCameraMode_ThirdPerson.generated.h"

class UCurveVector;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PF_API UPFCameraMode_ThirdPerson : public UPFCameraMode
{
	GENERATED_BODY()

public:

	UPFCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void UpdateView(float DeltaTime) override;

	//UCurveVector* TargetOffSetCurveNative;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	TObjectPtr<const UCurveVector> TargetOffSetCurve;
};
