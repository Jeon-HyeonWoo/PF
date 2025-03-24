// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFExperienceList.generated.h"

class UPFUserFacingExperience;

DECLARE_MULTICAST_DELEGATE(FOnUserFacingExperienceLoaded);

UCLASS()
class PF_API APFExperienceList : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFExperienceList();

	static APFExperienceList& Get() { return SingleTon; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	void UserFacingExperienceLoaded();
	
	bool IsUserFacingExperienceLoaded() { return bUserFacingExperienceLoaded; };
	
public:

	TArray<FPrimaryAssetId> ExperienceIdList;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<UPFUserFacingExperience*> ExperienceList;

	FOnUserFacingExperienceLoaded OnUserFacingExperienceLoaded;

private:

	static APFExperienceList SingleTon;

	bool bUserFacingExperienceLoaded = false;


};
