// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TimeStopper.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTimeStopper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API ITimeStopper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TimeStopActivate() = 0;

	virtual void TimeStopDeactivate() = 0;
	
	virtual void RegisterTimerStopTarget(AActor* InActor) = 0;

	virtual void UnregisterTimeStopTarget(AActor* InActor) = 0;
	
};
