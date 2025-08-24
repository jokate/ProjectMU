// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MUObjectPoolingManager.h"

#include "ObjectPoolingTarget.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UObjectPoolingTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IObjectPoolingTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ReturnToPooling() {}
	
	virtual bool CanActivateObject() { return false; }

	virtual void ActivateObject(FTransform Transform) {}
};
