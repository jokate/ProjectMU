﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "EquipmentOwner.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEquipmentOwner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IEquipmentOwner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void EquipItem(AActor* InActor) = 0;

	virtual const FGameplayTag& GetEquippingItemTag() = 0;
};
