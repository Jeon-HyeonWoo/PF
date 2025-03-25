// Fill out your copyright notice in the Description page of Project Settings.


#include "PFUserFacingExperience.h"
#include "CommonSessionSubsystem.h"


UCommonSession_HostSessionRequest* UPFUserFacingExperience::CreateHostingRequest() const
{
    const FString ExperienceName = ExperienceId.PrimaryAssetName.ToString();

    UCommonSession_HostSessionRequest* Result = NewObject<UCommonSession_HostSessionRequest>();
    Result->MapId = MapId;
    Result->ExtraArgs.Add(TEXT("Experience"), ExperienceName);

    return Result;
}
