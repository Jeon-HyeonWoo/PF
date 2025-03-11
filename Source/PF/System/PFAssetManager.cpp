// Fill out your copyright notice in the Description page of Project Settings.


#include "PFAssetManager.h"
#include "PF/PFLogChannels.h"

UPFAssetManager::UPFAssetManager()
{
}

UPFAssetManager& UPFAssetManager::Get()
{
	check(GEngine);

	if (UPFAssetManager* SingleTon = Cast<UPFAssetManager>(GEngine->AssetManager))
	{
		return *SingleTon;
	}

	UE_LOG(PFLog, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini(Project Settings); It must be PFAssetManager"));

	return *NewObject<UPFAssetManager>();
 }

bool UPFAssetManager::ShouldLogAssetLoad()
{
	/*
	* Proejct -> Property -> Debuging -> Command Arguement -> add "-LogAssetLoads"
	*/
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* UPFAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	//AssetPath ��ȿ�� �˻�
	if (AssetPath.IsValid()) 
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;

		// LogTime Check
		if (ShouldLogAssetLoad()) 
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronous Loaded Assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		//AssetManager ��ȿ�� �˻�
		if (UAssetManager::IsValid())
		{
			//AssetPath�� ���� �ε��� ��� return
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}
	
		/*
		* 'TryLoad'
		* - 'Find Cached Memory ���н��� Disk ���� ���', 'SyncLoad�� Blocking���'���� ���� ���������� ����.
		*/
		return AssetPath.TryLoad();
	}

	return nullptr;
}

void UPFAssetManager::AddLoadedAsset(const UObject* Asset)
{
	/*
	* ensureAlways(���Ἲ ����) : ���� �߰� �� ��ȿ�� ���� �� �α� �߰� 
	*/
	/*
	* ��Ƽ������κ��� ����, ������ ���� ����
	* FScopeLock(Thread-Safe, Race Condition) : �ϳ��� Thread�� LoadedAsset�� ������ �����ϵ��� Locking
	*/
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}
