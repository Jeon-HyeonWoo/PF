// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameInstance.h"
#include "Components/GameFrameworkComponentManager.h"
#include "PF/PFGameplayTags.h"

void UPFGameInstance::Init()
{
	Super::Init();
	/*
	* Component�� ���� ������ ���Ӽ��� ���� ���, ���� ���� ���� �ִµ�, FrameworkComponent�� �̸� ���������� �ʾ� Manager�� ���� �ʱ�ȭ ���¸� �����ش�.
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
