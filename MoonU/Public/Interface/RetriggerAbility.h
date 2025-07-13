// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RetriggerAbility.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URetriggerAbility : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IRetriggerAbility 
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void RetriggerAbility() = 0;
};
