// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "PFHeroComponent.generated.h"

class UPFCameraMode;

/**
 * Component that sets input and camera handling for player controlled pawns (or bots that simulate players)
 * - this depends on a pawnextensioncomponent to coordinate initialization
 * - 카메라 입력 등 플레이어가 제어하는 시스템의 초기화를 처리하는 컴포넌트
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class PF_API UPFHeroComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
	
public:

	UPFHeroComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); 
	
	/*
	* Define FeatureName
	*/
	static const FName Name_ActorFeatureName;

	/* 
	* UPawnComponent Interface
	*/
	virtual void OnRegister() final;
	virtual void BeginPlay() final;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final;
	
	/* 
	* IGameFrameworkInitStateInterface
	*/
	virtual FName GetFeatureName() const final { return Name_ActorFeatureName; }
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) final;
	/* Change Check Next InitStep */
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const final;
	/* Apply Changing the Initstate*/
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) final;
	virtual void CheckDefaultInitialization() final;

public:

	TSubclassOf<UPFCameraMode> DetermineCameraMode() const;
};
