// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCosmeticAnimationTypes.h"

TSubclassOf<UAnimInstance> FPFAnimLayerSelectionSet::SelectBestLayer(const FGameplayTagContainer& CosmeticTags) const
{
    for (const FPFAnimLayerSelectionEntry& Rule : LayerRules)
    {
        if ((Rule.Layer != nullptr) && CosmeticTags.HasAll(Rule.RequiredTags))
        {
            return Rule.Layer;
        }
    }

    return DefaultLayer;
}

USkeletalMesh* FPFAnimBodyStyleSelectionSet::SelectBestBodyStyle(const FGameplayTagContainer& CosmeticTags) const
{
    for (const FPFAnimBodyStyleSelectionEntry& Rule : MeshRules)
    {
        if ((Rule.Mesh) && CosmeticTags.HasAll(Rule.RequriedTags))
        {
            return Rule.Mesh;
        }
    }

    return DefaultMesh;
}


