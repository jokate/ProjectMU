// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MUEnum.h"
#include "Engine/DataAsset.h"
#include "MUPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly )
	TMap< int32, FName > CharacterAttributeRegistry;

	UPROPERTY( EditDefaultsOnly )
	TMap<int32, FName > CharacterSkillRegistry;

	UPROPERTY( EditDefaultsOnly )
	TMap<ESkillSlotType, FGameplayTag> SkillInputTags;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId( TEXT("MUEnforcement"));
	};
};
