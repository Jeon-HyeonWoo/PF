// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFUserFacingExperiencePortal.generated.h"

class USphereComponent;
class UTextRenderComponent;
class UPFUserFacingExperience;

UCLASS()
class PF_API APFUserFacingExperiencePortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFUserFacingExperiencePortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	void SetActorActivate();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalCollision")
	USphereComponent* PortalCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalCollision")
	UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PortalCollision")
	UPFUserFacingExperience* DesireExperience;

};
