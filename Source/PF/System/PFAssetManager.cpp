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
	//AssetPath 유효성 검사
	if (AssetPath.IsValid()) 
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;

		// LogTime Check
		if (ShouldLogAssetLoad()) 
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronous Loaded Assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		//AssetManager 유효성 검사
		if (UAssetManager::IsValid())
		{
			//AssetPath를 동기 로드한 결과 return
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}
	
		/*
		* 'TryLoad'
		* - 'Find Cached Memory 실패시의 Disk 접근 비용', 'SyncLoad의 Blocking방식'으로 인해 안전하지만 느림.
		*/
		return AssetPath.TryLoad();
	}

	return nullptr;
}

void UPFAssetManager::AddLoadedAsset(const UObject* Asset)
{
	/*
	* ensureAlways(무결성 보장) : 에셋 추가 전 유효성 검증 및 로그 추가 
	*/
	/*
	* 멀티스레드로부터 안전, 데이터 경쟁 방지
	* FScopeLock(Thread-Safe, Race Condition) : 하나의 Thread만 LoadedAsset에 접근이 가능하도록 Locking
	*/
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}
