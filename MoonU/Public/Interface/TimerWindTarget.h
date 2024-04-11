﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TimerWindTarget.generated.h"

/**
 * 
 */
// This class does not need to be modified.
UINTERFACE()
class UTimeWindTarget : public UInterface
{
	GENERATED_BODY()
};


class MOONU_API ITimeWindTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetTimeWind(bool InTimeWind) = 0;
	virtual const bool GetTimeWind() = 0;
};