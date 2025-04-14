// Fill out your copyright notice in the Description page of Project Settings.


#include "PFEquipmentInstance.h"
#include "PFEquipmentDefinition.h"
#include "GameFramework/Character.h"

UPFEquipmentInstance::UPFEquipmentInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

APawn* UPFEquipmentInstance::GetPawn() const
{
	return Cast<APawn>(GetOuter());
}

void UPFEquipmentInstance::OnEquipped()
{
	K2_OnEquipped();
}

void UPFEquipmentInstance::OnUnEquipped()
{
	K2_OnUnEquipped();
}

void UPFEquipmentInstance::SpawnEquipmentActors(const TArray<FPFEquipmentActorToSpawn>& ActorsToSpawn)
{
	if (APawn* OwningPawn = GetPawn())
	{
		USceneComponent* AttachTarget = OwningPawn->GetRootComponent();
		if (ACharacter* Character = Cast<ACharacter>(OwningPawn))
		{
			AttachTarget = Character->GetMesh();
		}

		for (const FPFEquipmentActorToSpawn& SpawnInfo : ActorsToSpawn)
		{
			//SpawnActorDeferred(Prepare Data), FinishSpawning(Create) Set
			AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnInfo.ActorToSpawn, FTransform::Identity, OwningPawn);
			NewActor->FinishSpawning(FTransform::Identity, /* bIsDefaultTransform = */true);

			NewActor->SetActorRelativeTransform(SpawnInfo.AttachTransform);

			NewActor->AttachToComponent(AttachTarget, FAttachmentTransformRules::KeepRelativeTransform, SpawnInfo.AttachSocket);

			SpawnedActors.Add(NewActor);
		}
	}
}

void UPFEquipmentInstance::DestroyEquipmentActors()
{
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}
}
