// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_ExperienceReady.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExperienceReadyAsyncDelegate);

class AGameStateBase;
class UPFExperienceDefinition;

UCLASS()
class PF_API UAsyncAction_ExperienceReady : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UAsyncAction_ExperienceReady(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UAsyncAction_ExperienceReady* WaitForExperienceReady(UObject* WorldContextObject);

	virtual void Activate() override;

	/* World and GameState Valid Check */
	void Step1_HandleGameStateSet(AGameStateBase* GameState);

	/* GameState is guaranteed to exist.
	* if CurrentExperience was Loaded, move on Step 4
	* do not reached currentexperience loaded, move on step 3
	*/
	void Step2_ListenToExperienceLoading(AGameStateBase* GameState);

	/* just move on next step */
	void Step3_HandleExperienceLoaded(const UPFExperienceDefinition* CurrentExperience);
	void Step4_BroadcastReady();

	UPROPERTY(BlueprintAssignable)
	FExperienceReadyAsyncDelegate OnReady;

	TWeakObjectPtr<UWorld> WorldPtr;
};
