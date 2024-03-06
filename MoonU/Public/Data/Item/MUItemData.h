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
	FText ItemText;
};

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

public :
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite)
	int32 ItemAmount = 0;

	bool operator==(const FInventoryData& Data) const
	{
		return ItemID == Data.ItemID;
	}
};