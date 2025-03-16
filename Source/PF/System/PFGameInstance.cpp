// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameInstance.h"
#include "Components/GameFrameworkComponentManager.h"
#include "PF/PFGameplayTags.h"

void UPFGameInstance::Init()
{
	Super::Init();
	/*
	* Component간 부착 순서에 종속성이 있을 경우, 얽힐 가능 성이 있는데, FrameworkComponent는 이를 보장해주지 않아 Manager를 통해 초기화 상태를 정해준다.
	*/
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);
	if (ensure(ComponentManager))
	{
		const FPFGameplayTags& GameplayTags = FPFGameplayTags::Get();

		ComponentManager->RegisterInitState(GameplayTags.InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(GameplayTags.InitState_DataAvailable, false, GameplayTags.InitState_Spawned);
		ComponentManager->RegisterInitState(GameplayTags.InitState_DataInitialized, false, GameplayTags.InitState_DataAvailable);
		ComponentManager->RegisterInitState(GameplayTags.InitState_GameplayReady, false, GameplayTags.InitState_DataInitialized);
	}
}

void UPFGameInstance::Shutdown()
{
	Super::Shutdown();
}
