// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/MUCraftData.h"
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

	UFUNCTION(BlueprintCallable)
	static const FItemPoolStructRow GetItemPoolRow(const FName& InPoolId);

	UFUNCTION(BlueprintCallable)
	static const FCraftDataRow GetCraftItemData(const FName& InItemId);

	UFUNCTION(BlueprintCallable)
	static void MoveItemToTargetIndex(AActor* OwnerActor, AActor* TargetActor, int32 StartIndex, int32 TargetIndex);

	UFUNCTION(BlueprintCallable)
	static void OwnInventoryItem(AActor* TargetActor, int32 ItemID, int32 Amount);

	UFUNCTION(BlueprintCallable)
	static void DisownInventoryItem(AActor* TargetActor, int32 ItemID, int32 Amount);
};
