// Fill out your copyright notice in the Description page of Project Settings.


#include "PFGameplayAbility_FromEquipment.h"
#include "PFEquipmentInstance.h"

UPFEquipmentInstance* UPFGameplayAbility_FromEquipment::GetAssociatedEquipment() const
{
    if (FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
    {
        return Cast<UPFEquipmentInstance>(Spec->SourceObject.Get());
    }

    return nullptr;
}
