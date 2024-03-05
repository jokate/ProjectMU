// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "InteractableTarget.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractableTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IInteractableTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnInteracted(AActor* InstigatorActor) = 0;

	virtual const bool IsInteractable(AActor* InstigatorActor) = 0;
	
	virtual const FGameplayTag& GetEntityTag() = 0;
};
