// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUPlayerHUD.h"

#include "MUDefines.h"
#include "Components/UI/GameplayTagWidgetContainer.h"
#include "UI/MUHUDWidget.h"

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

bool AMUPlayerHUD::IsGameplayWidgetInViewport()
{
	return GameplayTagWidgetContainer->IsGameplayWidgetInViewport();
}

void AMUPlayerHUD::HideAllWidgetForGameplay()
{
	GameplayTagWidgetContainer->HideAllWidgetForGameplay();
}

void AMUPlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	UMUHUDWidget* HUDWidget = Cast<UMUHUDWidget>(GameplayTagWidgetContainer->GetWidgetByGameplayTag(MU_UI_HUD));
	HUDWidget->SetAbilitySystemComponent(PlayerOwner->GetPawn());
	ShowWidgetByGameplayTag(MU_UI_HUD);
}
