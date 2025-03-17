// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "PFPawnExtensionComponent.generated.h"

class UPFPawnData;
/**
 * 초기화 전반을 조정하는 컴포넌트
 */
UCLASS()
class PF_API UPFPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{ 
	GENERATED_BODY()
	
public:

	UPFPawnExtensionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static UPFPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor)
	{
		return Actor ? Actor->FindComponentByClass<UPFPawnExtensionComponent>() : nullptr;
	}
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }
	void SetPawnData(const UPFPawnData* InPawnData);

	/*
	* Define FeatureName 
	*/
	static const FName Name_ActorFeatureName;

	/*
	* PawnComponent interface
	*/
	virtual void OnRegister() final;
	virtual void BeginPlay() final;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final;

	/*
	* IGameFrameworkInitStateInterface
	*/
	virtual FName GetFeatureName() const final { return Name_ActorFeatureName; }
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) final;
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const final;
	virtual void CheckDefaultInitialization() final;

	/* 
	* PawnData Cached
	*/
	UPROPERTY(EditInstanceOnly, Category = "PF | Pawn")
	TObjectPtr<const UPFPawnData> PawnData;
};
 