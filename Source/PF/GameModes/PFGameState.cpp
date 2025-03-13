// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameState.h"
#include "PF/GameModes/PFExperienceManagerComponent.h"

APFGameState::APFGameState()
{
	ExperienceManagerComponent = CreateDefaultSubobject<UPFExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}
