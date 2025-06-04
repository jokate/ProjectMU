// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MUPlayer.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMUPlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IMUPlayer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const int32 GetPlayerCharacterID() = 0;
};
