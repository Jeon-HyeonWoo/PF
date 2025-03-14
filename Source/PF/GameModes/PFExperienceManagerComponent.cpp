// Fill out your copyright notice in the Description page of Project Settings.


#include "PFExperienceManagerComponent.h"
#include "PF/System/PFAssetManager.h"
#include "PF/GameModes/PFExperienceDefinition.h"
#include "GameFeaturesSubsystemSettings.h"


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
		//Project Setting, AssetManager, Scan PrimaryDataAsset
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
		AssetClass = Cast<UClass>(AssetPath.TryLoad());
	}

	//Set CurrnetExperience Class Default Object
	const UPFExperienceDefinition* Experience = GetDefault<UPFExperienceDefinition>(AssetClass);
	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	{
		CurrentExperience = Experience;
	}

	StartExperienceLoad();
}

void UPFExperienceManagerComponent::StartExperienceLoad()
{
	//Current Experience = GetDefault?
	check(CurrentExperience);
	//Current Experience is not loading
	check(LoadState == EPFExperienceLoadState::Unload);

	//Start Experience Load
	LoadState = EPFExperienceLoadState::Loading;

	UPFAssetManager& AssetManager = UPFAssetManager::Get();

	TSet<FPrimaryAssetId> BundleAssetList;

	BundleAssetList.Add(CurrentExperience->GetPrimaryAssetId());

	TArray<FName> BundlesToLoad;
	{
		const ENetMode OwnerNetMode = GetOwner()->GetNetMode();
		bool bLoadClient = GIsEditor || (OwnerNetMode != NM_DedicatedServer);
		bool bLoadServer = GIsEditor || (OwnerNetMode != NM_Client);
		if (bLoadClient)
		{
			BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateClient);
		}
		if (bLoadServer)
		{
			BundlesToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateServer);
		}
		//BundlesToLoad = {TEXT("Client"), TEXT("Server")};
	}

	//call Load is completed Delegate
	FStreamableDelegate OnAssetsLoadedDelegate = FStreamableDelegate::CreateUObject(this, &ThisClass::OnExperienceLoadComplete);

	//Match BundleAassetList and BundleToLoad
	TSharedPtr<FStreamableHandle> Handle = AssetManager.ChangeBundleStateForPrimaryAssets(
		BundleAssetList.Array(),
		BundlesToLoad,
		{ }, false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority
	);

	//AsyncLoad_Load Complete
	if (!Handle.IsValid() || Handle->HasLoadCompleted())
	{
		FStreamableHandle::ExecuteDelegate(OnAssetsLoadedDelegate);
	}
	else //if Load failed.
	{
		Handle->BindCompleteDelegate(OnAssetsLoadedDelegate);
		Handle->BindCancelDelegate(FStreamableDelegate::CreateLambda([OnAssetsLoadedDelegate]()
			{
				OnAssetsLoadedDelegate.ExecuteIfBound();
			}
		));
	}
}

void UPFExperienceManagerComponent::OnExperienceLoadComplete()
{
	static int32 OnExperienceLoadComplete_FrameNumber = GFrameNumber;

	OnExperienceFullLoadCompleted();
}

void UPFExperienceManagerComponent::OnExperienceFullLoadCompleted()
{
	check(LoadState != EPFExperienceLoadState::Loaded);

	LoadState = EPFExperienceLoadState::Loaded;
	OnExperienceLoaded.Broadcast(CurrentExperience);
	OnExperienceLoaded.Clear();
}

const UPFExperienceDefinition* UPFExperienceManagerComponent::GetCurrentExperienceChecked() const
{
	check(LoadState == EPFExperienceLoadState::Loaded);
	check(CurrentExperience != nullptr);

	return CurrentExperience;
}
