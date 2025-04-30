// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PF/Equipment/PFGameplayAbility_FromEquipment.h"
#include "PFGameplayAbility_RangedWeapon.generated.h"

/**
 * 
 */
class UPFRangedWeaponInstance;

UENUM(BlueprintType)
enum class EPFAbilityTargetingSource : uint8
{
	/* Camera ±‚¡ÿ¿∏∑Œ √—±∏ º≥¡§, 3¿Œƒ™ FPS */
	CameraTowardsFocus,
};


UCLASS()
class PF_API UPFGameplayAbility_RangedWeapon : public UPFGameplayAbility_FromEquipment
{
	GENERATED_BODY()
	
public:

	struct FRangedWeaponFiringInput
	{
		FVector StartTrace;
		FVector EndAim;
		FVector AimDir;

		UPFRangedWeaponInstance* WeaponData = nullptr;
		bool bCanPlayBulletFX = false;

		FRangedWeaponFiringInput()
			: StartTrace(ForceInitToZero)
			, EndAim(ForceInitToZero)
			, AimDir(ForceInitToZero)
		{ }
	};

public:

	UPFGameplayAbility_RangedWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:

	UFUNCTION(BlueprintCallable)
	void StartRangedWeaponTargeting();

	//Targeting Function
	void PerformLocalTargeting(TArray<FHitResult>& OutHits);

	FTransform GetTargetingTransform(APawn* SourcePawn, EPFAbilityTargetingSource Source);

	FVector GetWeaponTargetingSourceLocation() const;

	void TraceBulletsInCartridge(const FRangedWeaponFiringInput& InputData, TArray<FHitResult>& OutHits);

	FHitResult DoSingleBulletTrace(const FVector& StartTrace, const FVector& EndTrace, float SweepRadius, bool bIsSimulated, TArray<FHitResult>& OutHits) const;

	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace, float SweepRadius, bool bIsSimulated, TArray<FHitResult>& OutHitResults) const;

	void AddAdditionalTraceIgnoreActors(FCollisionQueryParams& TraceParams) const;

	ECollisionChannel DetermineTraceChannel(FCollisionQueryParams& TraceParams, bool bIsSimulated) const;

	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);

	/* Called When target data is ready */
	UFUNCTION(BlueprintImplementableEvent)
	void OnRangeWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);

	UPFRangedWeaponInstance* GetWeaponInstance();
};
