// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFWeaponInstance.h"
#include "PFRangedWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class PF_API UPFRangedWeaponInstance : public UPFWeaponInstance
{
	GENERATED_BODY()

public: 
	
	/* Effective Range */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponConfig", meta = (FourceUnits = cm))
	float MaxDamageRange = 25000.0f;
	
	/* Sphere Trace Sweep */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponConfig", meta = (FourceUnits = cm))
	float BulletTraceWeaponRadius = 0.0f;
};
