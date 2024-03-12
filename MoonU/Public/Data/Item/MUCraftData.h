// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "MUCraftData.generated.h"

USTRUCT(BlueprintType)
struct FCraftItemRow
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NeedAmount;
};

USTRUCT(BlueprintType)
struct FCraftDataRow : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CraftItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCraftItemRow> NeedItemsToCraft;
};


USTRUCT(BlueprintType)
struct FCraftBuildingDataRow : public FTableRowBase
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> ItemsCanCraft;
};