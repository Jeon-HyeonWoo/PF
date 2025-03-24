// Fill out your copyright notice in the Description page of Project Settings.


#include "PFExperienceList.h"
#include "PF/GameModes/PFUserFacingExperience.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "PF/System/PFAssetManager.h"


// Sets default values
APFExperienceList::APFExperienceList()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APFExperienceList::BeginPlay()
{
	Super::BeginPlay();
	
	UPFAssetManager& AssetManager = UPFAssetManager::Get();

	if (AssetManager.GetPrimaryAssetIdList(FName("PFUserFacingExperience"), ExperienceIdList))
	{
		FStreamableDelegate OnAssetsLoadedDelegate = FStreamableDelegate::CreateUObject(this, &ThisClass::UserFacingExperienceLoaded);
		TSharedPtr<FStreamableHandle> Handle = AssetManager.LoadPrimaryAssets(ExperienceIdList);
		if (Handle.IsValid() || Handle->HasLoadCompleted())
		{
			FStreamableHandle::ExecuteDelegate(OnAssetsLoadedDelegate);
		}
	}
}

// Called every frame
void APFExperienceList::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APFExperienceList::UserFacingExperienceLoaded()
{
	UPFAssetManager& AssetManager = UPFAssetManager::Get();

	for (const FPrimaryAssetId& AssetId : ExperienceIdList)
	{
		if (UObject* LoadedAsset = AssetManager.GetPrimaryAssetObject(AssetId))
		{
			if (UPFUserFacingExperience* UserExperience = Cast<UPFUserFacingExperience>(LoadedAsset))
			{
				ExperienceList.Add(UserExperience);
			}
		}
	}
	bUserFacingExperienceLoaded = true;

	OnUserFacingExperienceLoaded.Broadcast();
}



