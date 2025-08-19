// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MUDataPrimaryAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUDataPrimaryAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CharacterDataRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName InputMapperDataRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillDataRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StageInfoDataRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StageDataRegistryType = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MonsterSpawnDataRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillTreeWidgetDatRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TopMenuWidgetDataRegistryType = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ProjectileRegistryType = NAME_None;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId( TEXT("Data"), GetFName());
	};
};
