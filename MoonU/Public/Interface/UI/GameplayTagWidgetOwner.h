// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "GameplayTagWidgetOwner.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGameplayTagWidgetOwner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IGameplayTagWidgetOwner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UUserWidget* GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag) = 0;

	virtual void ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag) = 0;

	virtual void HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag) = 0;

	virtual bool IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag) = 0;

	virtual bool IsGameplayWidgetInViewport() = 0;

	virtual void HideAllWidgetForGameplay() = 0;
};
