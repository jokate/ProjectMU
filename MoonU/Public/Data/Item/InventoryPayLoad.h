// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUItemData.h"
#include "UObject/Object.h"
#include "InventoryPayLoad.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MOONU_API UInventoryPayLoad : public UObject
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventoryData PayloadInventoryData;
};
