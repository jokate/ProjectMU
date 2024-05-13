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
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameplayEffect> EffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsStackable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemMaxAmount = 0;
};

USTRUCT(BlueprintType)
struct FInventorySlotData
{
	GENERATED_BODY()

	FInventorySlotData()
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemAmount = 0;

	bool operator==(const FInventorySlotData& InventorySlotData) const
	{
		return ItemID == InventorySlotData.ItemID;
	}
	
	bool operator==(int32 InID) const
	{
		return ItemID == InID;
	}
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

USTRUCT(BlueprintType)
struct FItemDropPool
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item ID")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Amount")
	int32 MinAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Amount")
	int32 MaxAmount;
};

USTRUCT(BlueprintType)
struct FItemDropData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemDropPool> DropPools;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Percentage = 0.f;
};


USTRUCT(BlueprintType)
struct FItemDropTableRow : public FTableRowBase
{
	GENERATED_BODY()

	FItemDropTableRow()
	{
		
	}
	
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	TArray<FItemDropData> DropData;
};
