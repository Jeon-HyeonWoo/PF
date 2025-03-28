// Fill out your copyright notice in the Description page of Project Settings.


#include "PFExperienceManagerComponent.h"
#include "PF/System/PFAssetManager.h"				//For Load
#include "PF/GameModes/PFExperienceDefinition.h"	//Manged obj
//GameFeature
#include "GameFeaturesSubsystemSettings.h"
#include "GameFeaturesSubsystem.h"


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

	static int32 StartExperienceLoad_FrameNumber = GFrameNumber;
}

void UPFExperienceManagerComponent::OnExperienceLoadComplete()
{
	static int32 OnExperienceLoadComplete_FrameNumber = GFrameNumber;

	check(LoadState == EPFExperienceLoadState::Loading);
	check(CurrentExperience);

	GameFeaturePluginURLs.Reset();

	auto CollectGameFeaturePluginURLs = [This = this](const UPrimaryDataAsset* Context, const TArray<FString>& FeaturePluginList)
		{
			for (const FString& PluginName : FeaturePluginList)
			{
				FString PluginURL;
				if (UGameFeaturesSubsystem::Get().GetPluginURLByName(PluginName, PluginURL))
				{
					This->GameFeaturePluginURLs.AddUnique(PluginURL);
				}
			}
		};

	CollectGameFeaturePluginURLs(CurrentExperience, CurrentExperience->GameFeaturesToEnable);

	NumGameFeaturePluginsLoading = GameFeaturePluginURLs.Num();
	if (NumGameFeaturePluginsLoading)
	{
		LoadState = EPFExperienceLoadState::LoadingGameFeature;
		for (const FString& PluginURL : GameFeaturePluginURLs)
		{
			/*
			* Load GameFeature and Activate
			*/
			UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginURL, FGameFeaturePluginLoadComplete::CreateUObject(this, &ThisClass::OnGameFeaturePluginLoadCompelete));
		}
	}
	else //Experience Definition has no GameFeatures
	{
		OnExperienceFullLoadCompleted();
	}

}

void UPFExperienceManagerComponent::OnGameFeaturePluginLoadCompelete(const UE::GameFeatures::FResult& Result)
{
	NumGameFeaturePluginsLoading--;
	if (NumGameFeaturePluginsLoading == 0)
	{
		OnExperienceFullLoadCompleted();
	}
	
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
