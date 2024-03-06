// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "MUItemData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsStackable : 1;
};

USTRUCT(BlueprintType)
struct FInventoryUpgradeData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag UpgradeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradeAmount = 0;

	bool operator==(const FInventoryUpgradeData& UpgradeData) const
	{
		return UpgradeTag.MatchesTag(UpgradeData.UpgradeTag) && UpgradeAmount == UpgradeData.UpgradeAmount;
	}

	bool operator==(const FGameplayTag& InGameplayTag) const
	{
		return UpgradeTag.MatchesTag(InGameplayTag);
	}
	
};

FORCEINLINE uint32 GetTypeHash(const FInventoryUpgradeData& InUpgradeData)
{
	return FCrc::MemCrc32(&InUpgradeData, sizeof(FInventoryUpgradeData));
}
//
USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

public :
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryUpgradeData> UpgradeDatas;
	
	bool operator==(const FInventoryData& Data) const
	{
		return ItemID == Data.ItemID && UpgradeDatas == Data.UpgradeDatas;
	}
};


USTRUCT(BlueprintType)
struct FInventoryPoolData
{
	GENERATED_BODY()

public :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FInventoryData Data;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Amount;
};

FORCEINLINE uint32 GetTypeHash(const FInventoryData& InUpgradeData)
{
	return FCrc::MemCrc32(&InUpgradeData, sizeof(FInventoryData));
}

USTRUCT(BlueprintType)
struct FItemDropPool
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinAmount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryUpgradeData> UpgradeData;
};

USTRUCT(BlueprintType)
struct FItemDropData
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemDropPool> DropPools;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Percentage = 0.0f;
};


USTRUCT(BlueprintType)
struct FItemPoolStructRow : public FTableRowBase
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FItemDropData> ItemPoolingData;
};


USTRUCT(BlueprintType)
struct FItemDisplayDataRow : public FTableRowBase
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	TObjectPtr<UTexture2D> ImageTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Description")
	FText ItemDescription;
};