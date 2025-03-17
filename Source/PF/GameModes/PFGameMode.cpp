// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameMode.h"
#include "PFGameState.h"
#include "PF/Player/PFPlayerController.h"
#include "PF/Player/PFPlayerState.h"
#include "PF/Character/PFCharacter.h"
#include "PF/Character/PFPawnData.h"
#include "PF/GameModes/PFExperienceManagerComponent.h"
#include "PF/GameModes/PFExperienceDefinition.h"
#include "PF/Character/PFPawnExtensionComponent.h"


APFGameMode::APFGameMode()
{
	GameStateClass = APFGameState::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();
	PlayerStateClass = APFPlayerState::StaticClass();
	DefaultPawnClass = APFCharacter::StaticClass();
}

void APFGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void APFGameMode::InitGameState()
{
	Super::InitGameState();

	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

UClass* APFGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (const UPFPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void APFGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	/* Experience is not Loaded, Player can not enter the game */
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
	
}

APawn* APFGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (UPFPawnExtensionComponent* PawnExtComp = UPFPawnExtensionComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const UPFPawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					PawnExtComp->SetPawnData(PawnData);
				}
			}
			SpawnedPawn->FinishSpawning(SpawnTransform);
			return SpawnedPawn;
		}
	}

	return nullptr;
}

void APFGameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("PFExperienceDefinition"), FName("BP_DefaultExperience"));
	}

	OnMatchAssignmentGiven(ExperienceId);
}

void APFGameMode::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	check(ExperienceId.IsValid());

	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	ExperienceManagerComponent->ServerSetCurrentExperience(ExperienceId);
}

bool APFGameMode::IsExperienceLoaded() const
{
	check(GameState);
	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	
	return ExperienceManagerComponent->IsExperienceLoaded();
}

void APFGameMode::OnExperienceLoaded(const UPFExperienceDefinition* CurrentExperience)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);

		if (PC && PC->GetPawn() == nullptr)
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
}

const UPFPawnData* APFGameMode::GetPawnDataForController(const AController* InController) const
{
	//PlayerState Cached Pawn Data
	if (InController)
	{
		if (const APFPlayerState* PFPS = InController->GetPlayerState<APFPlayerState>())
		{
			if (const UPFPawnData* PawnData = PFPS->GetPawnData<UPFPawnData>())
			{
				return PawnData;
			}
		}
	}

	//if the PlayerState dose not have cached pawn data, brings currentexperience in Managercomponent
	check(GameState); 
	UPFExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UPFExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	if (ExperienceManagerComponent->IsExperienceLoaded())
	{
		const UPFExperienceDefinition* Experience = ExperienceManagerComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData)
		{
			return Experience->DefaultPawnData;
		}
	}

	return nullptr;
 }
