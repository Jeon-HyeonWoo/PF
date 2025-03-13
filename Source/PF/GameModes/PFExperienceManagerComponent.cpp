// Fill out your copyright notice in the Description page of Project Settings.


#include "PFExperienceManagerComponent.h"

void UPFExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(FOnPFExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.Execute(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}
