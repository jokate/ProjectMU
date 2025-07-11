﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIEnum.h"
#include "UObject/Interface.h"
#include "MUEnemy.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMUEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEnemyDeath, AActor*, Self );

class MOONU_API IMUEnemy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const FOnEnemyDeath& GetEnemyDeath() = 0;
};

