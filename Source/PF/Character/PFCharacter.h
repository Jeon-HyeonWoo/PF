// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "AbilitySystemInterface.h"
#include "PFCharacter.generated.h"

class UPFPawnExtensionComponent;
class UPFCameraComponent;

UCLASS()
class PF_API APFCharacter : public AModularCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APFCharacter();

public:
	//AbilitySystemInterface Override
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PF | Charater")
	TObjectPtr<UPFPawnExtensionComponent> PawnExtComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PF | Charater")
	TObjectPtr<UPFCameraComponent> CameraComponent;
};
