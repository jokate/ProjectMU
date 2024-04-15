// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Patroller.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPatroller : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IPatroller
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void IncrementPatrolRoute() = 0;
	
	virtual const FVector GetPositionForSpline() = 0;
};
