// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUPlayerHUD.h"

#include "Components/UI/GameplayTagWidgetContainer.h"

AMUPlayerHUD::AMUPlayerHUD()
{
	GameplayTagWidgetContainer = CreateDefaultSubobject<UGameplayTagWidgetContainer>("Widget Container");	
}

UUserWidget* AMUPlayerHUD::GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	return GameplayTagWidgetContainer->GetWidgetByGameplayTag(InGameplayTag);
}

void AMUPlayerHUD::ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	GameplayTagWidgetContainer->ShowWidgetByGameplayTag(InGameplayTag);
}

void AMUPlayerHUD::HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	GameplayTagWidgetContainer->HideWidgetByGameplayTag(InGameplayTag);
}

bool AMUPlayerHUD::IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag)
{
	return GameplayTagWidgetContainer->IsWidgetByGameplayTagInViewport(InGameplayTag);
}
