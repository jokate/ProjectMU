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
	TSubclassOf<class UGameplayEffect> EffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsStackable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemMaxAmount = 0;
};
