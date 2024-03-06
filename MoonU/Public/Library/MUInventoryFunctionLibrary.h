// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/MUItemData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MUInventoryFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public :
	UFUNCTION(BlueprintCallable)
	static const FItemDataRow GetItemDataRow(const FName& InItemId);

	UFUNCTION(BlueprintCallable)
	static const FItemDataRow GetItemDataRowById(const int32 InItemId);
};
