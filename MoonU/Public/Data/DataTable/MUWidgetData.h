// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "MUWidgetData.generated.h"


USTRUCT(BlueprintType)
struct FInteractionBoardData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InteractionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractionText;
};
