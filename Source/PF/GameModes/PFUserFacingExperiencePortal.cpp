// Fill out your copyright notice in the Description page of Project Settings.


#include "PFUserFacingExperiencePortal.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "PF/GameModes/PFExperienceList.h"
#include "PF/GameModes/PFUserFacingExperience.h"
#include "Kismet/GameplayStatics.h"
#include "PF/PFLogChannels.h"

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

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APFExperienceList::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		APFExperienceList* List = Cast<APFExperienceList>(FoundActors[0]);
		if (!List)
		{
			UE_LOG(PFLog, Error, TEXT("Can not Found UserExperienceList"));
		}
		else
		{
			List->OnUserFacingExperienceLoaded.AddUObject(this, &ThisClass::SetActorActivate);
		}
	} 

}

// Called every frame
void APFUserFacingExperiencePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APFUserFacingExperiencePortal::SetActorActivate()
{
	FString MapIdOnly;
	FString FullPath = DesireExperience->MapId.PrimaryAssetName.ToString();
	FullPath.Split(TEXT("/"), nullptr, &MapIdOnly, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	TextRenderComponent->SetText(FText::FromString(MapIdOnly));
}

