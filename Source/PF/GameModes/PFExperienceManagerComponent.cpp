// Fill out your copyright notice in the Description page of Project Settings.


#include "PFExperienceManagerComponent.h"
#include "PF/System/PFAssetManager.h"

void UPFExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}

void UPFExperienceManagerComponent::ServerSetCurrentExperience(FPrimaryAssetId ExperienceId)
{
	UPFAssetManager& AssetManager = UPFAssetManager::Get();

	TSubclassOf<UPFExperienceDefinition> AssetClass;
	{
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
	}
}
