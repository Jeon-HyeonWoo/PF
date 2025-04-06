// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCosmeticAnimationTypes.h"

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
