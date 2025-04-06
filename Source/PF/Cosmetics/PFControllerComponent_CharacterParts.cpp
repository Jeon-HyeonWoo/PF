// Fill out your copyright notice in the Description page of Project Settings.


#include "PFControllerComponent_CharacterParts.h"
#include "PFPawnComponent_CharacterParts.h"

UPFControllerComponent_CharacterParts::UPFControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPFControllerComponent_CharacterParts::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (AController* OwningController = GetController<AController>())
		{
			OwningController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPossessedPawnChanged);
		}
	}
}

void UPFControllerComponent_CharacterParts::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveAllCharacterParts();
	Super::EndPlay(EndPlayReason);
}

UPFPawnComponent_CharacterParts* UPFControllerComponent_CharacterParts::GetPawnCustomizer() const
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		return ControlledPawn->FindComponentByClass<UPFPawnComponent_CharacterParts>();
	}

	return nullptr;
}

void UPFControllerComponent_CharacterParts::AddCharacterPart(const FPFCharacterPart& NewPart)
{
	AddCharacterPartInternal(NewPart);
}

void UPFControllerComponent_CharacterParts::AddCharacterPartInternal(const FPFCharacterPart& NewPart)
{
	FPFControllerCharacterPartEntry& NewEntry = CharacterParts.AddDefaulted_GetRef();

	NewEntry.Part = NewPart;

	if (UPFPawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		NewEntry.Handle = PawnCustomizer->AddCharacterPart(NewPart);
	}
}

void UPFControllerComponent_CharacterParts::RemoveAllCharacterParts()
{
	if (UPFPawnComponent_CharacterParts* PawnCustumizer = GetPawnCustomizer())
	{
		for (FPFControllerCharacterPartEntry& Entry : CharacterParts)
		{
			PawnCustumizer->RemoveCharaterPart(Entry.Handle);
		}
	}
	CharacterParts.Reset();
}

void UPFControllerComponent_CharacterParts::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (UPFPawnComponent_CharacterParts* OldCustomizer = OldPawn ? OldPawn->FindComponentByClass<UPFPawnComponent_CharacterParts>() : nullptr)
	{
		for (FPFControllerCharacterPartEntry& Entry : CharacterParts)
		{
			OldCustomizer->RemoveCharaterPart(Entry.Handle);
			Entry.Handle.Reset();
		}
	}

	if (UPFPawnComponent_CharacterParts* NewCustumizer = NewPawn ? NewPawn->FindComponentByClass<UPFPawnComponent_CharacterParts>() : nullptr)
	{
		for (FPFControllerCharacterPartEntry& Entry : CharacterParts)
		{
			check(!Entry.Handle.IsValid());
			Entry.Handle = NewCustumizer->AddCharacterPart(Entry.Part);
		}
	}
}
