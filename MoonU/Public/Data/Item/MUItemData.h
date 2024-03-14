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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemMaxAmount = 0;
};

USTRUCT(BlueprintType)
struct FEquipmentUpgradeData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag UpgradeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradeAmount = 0;

	bool operator==(const FEquipmentUpgradeData& UpgradeData) const
	{
		return UpgradeTag.MatchesTag(UpgradeData.UpgradeTag) && UpgradeAmount == UpgradeData.UpgradeAmount;
	}

	bool operator==(const FGameplayTag& InGameplayTag) const
	{
		return UpgradeTag.MatchesTag(InGameplayTag);
	}
	
};

FORCEINLINE uint32 GetTypeHash(const FEquipmentUpgradeData& InUpgradeData)
{
	return FCrc::MemCrc32(&InUpgradeData, sizeof(FEquipmentUpgradeData));
}
//
USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

public :
	FInventoryData() {};

	FInventoryData(const int32 ItemID, const int32 Amount) : ItemID(ItemID), Amount(Amount) {}
	
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
	
	bool operator==(const FInventoryData& Data) const
	{
		return ItemID == Data.ItemID && Amount == Data.Amount;
	}

	bool operator==(int32 InID) const
	{
		return ItemID == InID;
	}
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
	TSoftObjectPtr<UTexture2D> ImageTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
	FText ItemText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Description")
	FText ItemDescription;
};