// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactor.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IInteractor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TryInteract() = 0;

	virtual void SetCachedInteractionTarget(AActor* TargetActor) = 0;
};
