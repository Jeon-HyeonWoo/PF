// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlayerController.h"
#include "PF/Camera/PFPlayerCameraManager.h"
#include "PFPlayerState.h"
#include "PF/AbilitySystem/PFAbilitySystemComponent.h"

APFPlayerController::APFPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = APFPlayerCameraManager::StaticClass();
}

void APFPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UPFAbilitySystemComponent* PFASC = GetPFAbilitySystemComponent())
	{
		PFASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

APFPlayerState* APFPlayerController::GetPFPlayerState() const
{
	return CastChecked<APFPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UPFAbilitySystemComponent* APFPlayerController::GetPFAbilitySystemComponent() const
{
	const APFPlayerState* PFPS = GetPFPlayerState();
	return (PFPS ? PFPS->GetPFAbilitySystemComponent() : nullptr);
}
