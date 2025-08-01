﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "MUPlayerHUD.generated.h"

class UMUHUDWidget;

/**
 * 
 */
UCLASS()
class MOONU_API AMUPlayerHUD : public AHUD, public IGameplayTagWidgetOwner
{
 	GENERATED_BODY()

public :
	AMUPlayerHUD();

#pragma region IGameplayTagWidgetOwner
	virtual UUserWidget* GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual void ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual void HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag) override;

	virtual bool IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag) override;

	virtual bool IsGameplayWidgetInViewport() override;

	virtual void HideAllWidgetForGameplay() override;
#pragma endregion

	virtual void BeginPlay() override;

	UPROPERTY( EditDefaultsOnly )
	FGameplayTag InitialTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UGameplayTagWidgetContainer> GameplayTagWidgetContainer;
};
