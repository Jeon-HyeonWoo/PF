// Fill out your copyright notice in the Description page of Project Settings.


#include "PFUserFacingExperiencePortal.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "PF/GameModes/PFExperienceList.h"
#include "PF/GameModes/PFUserFacingExperience.h"

// Sets default values
APFUserFacingExperiencePortal::APFUserFacingExperiencePortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create PortalCollision
	{
		PortalCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		PortalCollision->InitSphereRadius(250.0f);
	}

	{
		TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	}
}

// Called when the game starts or when spawned
void APFUserFacingExperiencePortal::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	APFExperienceList& List = APFExperienceList::Get();
	List.OnUserFacingExperienceLoaded.AddUObject(this, &ThisClass::SetActorActivate);
	
}

// Called every frame
void APFUserFacingExperiencePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APFUserFacingExperiencePortal::SetActorActivate()
{
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	TextRenderComponent->SetText(FText::FromName(DesireExperience->MapId.PrimaryAssetName));
}

