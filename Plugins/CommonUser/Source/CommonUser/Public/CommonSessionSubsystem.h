// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommonSessionSubsystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)

class COMMONUSER_API UCommonSession_HostSessionRequest : public UObject
{
	GENERATED_BODY()

public:

	/* TextFrom -> MapId */
	FString GetMapName() const;

	/* Create final URL for send ServerTravel */
	FString ConstructTravelURL() const;

	/* Path of MapId */
	UPROPERTY(BlueprintReadWrite, Category = "Session")
	FPrimaryAssetId MapId;

	/*  */
	UPROPERTY(BlueprintReadWrite, Category = "Session")
	TMap<FString, FString> ExtraArgs;

};

UCLASS()
class COMMONUSER_API UCommonSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	UCommonSessionSubsystem() { }
	
	UFUNCTION(BlueprintCallable, Category = Session)
	void HostSesstion(APlayerController* HostingPlayer, UCommonSession_HostSessionRequest* Request);

	FString PendingTravelURL;
	
	
};
