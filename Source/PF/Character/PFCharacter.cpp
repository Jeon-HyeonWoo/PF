// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacter.h"
#include "PFPawnExtensionComponent.h"
#include "PF/Character/PFPawnExtensionComponent.h"

// Sets default values
APFCharacter::APFCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	//PawnExtensionComponent
	{
		PawnExtComponent = CreateDefaultSubobject<UPFPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	}
}

// Called when the game starts or when spawned
void APFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnExtComponent->SetupPlayerInputComponent();
}

