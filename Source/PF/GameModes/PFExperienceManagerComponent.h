// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "GameFeaturePluginOperationResult.h"
#include "PFExperienceManagerComponent.generated.h"

class UPFExperienceDefinition;

enum class EPFExperienceLoadState
{
	Unload,
	Loading,
	LoadingGameFeature,
	ExecutingActions,	//GameFeatures action
	Loaded,
	Deactivating,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPFExperienceLoaded, const UPFExperienceDefinition*);

/**
 * 
 */
UCLASS()
class PF_API UPFExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:

	bool IsExperienceLoaded() { return (LoadState == EPFExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }

	/* Check CurrentExperience State is Loaded? */
	void CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate&& Delegate);

	/* 
	* Given GameMode::OnMatchAssignmentGiven,
	* Apply the Scanned path from AssetManager to current experience
	*/
	void ServerSetCurrentExperience(FPrimaryAssetId ExperienceId);

	/* Match Experience Bundles */
	void StartExperienceLoad();

	/* call experience loaded with out problems, Experience and other things load*/
	void OnExperienceLoadComplete();

	/* All OnGameFeature Load Completed, Call Experience Full Load */
	void OnGameFeaturePluginLoadCompelete(const UE::GameFeatures::FResult& Result);

	/* BoardCast Experience Load Complete, GameFeature is Guaranteed to be activated, start to Gemefeature action activate */
	void OnExperienceFullLoadCompleted();

	const UPFExperienceDefinition* GetCurrentExperienceChecked() const;
public:

	UPROPERTY()
	TObjectPtr<const UPFExperienceDefinition> CurrentExperience;
	
	EPFExperienceLoadState LoadState = EPFExperienceLoadState::Unload;

	FOnPFExperienceLoaded OnExperienceLoaded;

public:
	//GameFeatures Activate
	int32 NumGameFeaturePluginsLoading = 0;
	TArray<FString> GameFeaturePluginURLs;

};
