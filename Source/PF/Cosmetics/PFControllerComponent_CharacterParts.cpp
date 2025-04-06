// Fill out your copyright notice in the Description page of Project Settings.


#include "PFControllerComponent_CharacterParts.h"
#include "PFPawnComponent_CharacterParts.h"

UPFControllerComponent_CharacterParts::UPFControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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
