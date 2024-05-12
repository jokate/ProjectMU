// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	virtual void UseItem(int32 SlotIndex) = 0 ;

	virtual void AddItem(int32 ItemId, int32 ItemAmount) = 0;
};
