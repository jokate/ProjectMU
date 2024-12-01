// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetManager.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTargetManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API ITargetManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsTargetValid() const = 0;

	virtual AActor* GetActorTarget() const = 0;
	
	virtual void SetupTarget(AActor* NewTarget) = 0;

	virtual FVector GetTargetLocation() const = 0;
	
	virtual void SetupTargetLocation(FVector NewTargetLocation) = 0;
};
