// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHUDWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IHUDWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnOxygenChanged(float InOxygen) = 0;

	virtual void OnStaminaChanged(float InStamina) = 0;
	
	virtual void OnInteratableObjectInBound(AActor* InteractableActor) = 0;
};
