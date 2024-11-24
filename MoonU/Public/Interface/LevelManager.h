// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelManager.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULevelManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API ILevelManager
{
	GENERATED_BODY()

public:
	virtual void LevelUp() = 0;

	virtual void SetLevel(int32 InLevel) = 0;
};
