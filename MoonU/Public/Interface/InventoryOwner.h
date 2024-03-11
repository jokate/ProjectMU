// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/MUItemData.h"
#include "UObject/Interface.h"
#include "InventoryOwner.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInventoryOwner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IInventoryOwner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OwnInventory(const FInventoryData& Item) = 0;

	virtual void DisOwnInventory(const FInventoryData& Item) = 0;

	virtual int32 GetMaxStorageAmount() const = 0;

	virtual const TArray<FInventoryData>& GetTotalInventoryData() = 0;
};
