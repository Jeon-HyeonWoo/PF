// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PFAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PF_API UPFAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	//Constrcutor
	UPFAssetManager();
	
	//Get SingleTon Instance
	static UPFAssetManager& Get();

	/*
	* GameplayTag Native Initialize Tags
	*/
	virtual void StartInitialLoading() final;

	//FScopeLogTime(Performance, Runtime-Perform üũ��) ��� ���� Ȯ��
	static bool ShouldLogAssetLoad();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	//Multi Thread�� ���� �������� ���� AssetManager�� ���� ���Ἲ ���� �� ������ ���� ���� �Լ�. 
	void AddLoadedAsset(const UObject* Asset);

public:

	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template<typename AssetType> 
	static TSubclassOf<AssetType> GetSubclass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);


public:

	// Caching Variable - Garbage Collection(.GC)���� Loaded�� Asset���� ����
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	FCriticalSection SyncObject;

};

template<typename AssetType>
AssetType* UPFAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();
	//��� ��ȿ�� �˻�
	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();

		//LoadedAsset�� ���ٸ� Load
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to Load Asset [%s]"), *AssetPointer.ToString());
		}

		//LoadedAsset�� �ִٸ�, Caching
		if (LoadedAsset && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}
	return LoadedAsset;
}

template<typename AssetType>
TSubclassOf<AssetType> UPFAssetManager::GetSubclass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to Load Asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedAssets));
		}
	}

	return LoadedSubclass;
}
