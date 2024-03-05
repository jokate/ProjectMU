// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/GameplayTagWidgetContainer.h"

#include "UnrealWidgetFwd.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"


// Sets default values for this component's properties
UGameplayTagWidgetContainer::UGameplayTagWidgetContainer()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UUserWidget* UGameplayTagWidgetContainer::GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{	if (WidgetContainer.Contains(InGameplayTag) == false)
	{
		return nullptr;
	}

	return WidgetContainer[InGameplayTag];
}

void UGameplayTagWidgetContainer::ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	AActor* OwnerActor = GetOwner();

	if (OwnerActor == nullptr)
	{
		return;
	}

	AHUD* HUD = Cast<AHUD>(OwnerActor);
	
	if (HUD == nullptr)
	{
		return;
	}

	auto* PC = HUD->GetOwningPlayerController();

	if (PC == nullptr)
	{
		return;
	}
		
	if (WidgetClassMapping.Contains(InGameplayTag) == false)
	{
		return;
	}
	
	if (WidgetContainer.Contains(InGameplayTag) == false)
	{
		TSubclassOf<UUserWidget> WidgetClass = WidgetClassMapping[InGameplayTag];
		
		if (WidgetClass == nullptr)
		{
			return;
		}

		UUserWidget* InstanceWidget = CreateWidget<UUserWidget>(PC, WidgetClass);
		WidgetContainer.Emplace(InGameplayTag, InstanceWidget);
	}

	WidgetContainer[InGameplayTag]->AddToViewport();
}

void UGameplayTagWidgetContainer::HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	AActor* OwnerActor = GetOwner();

	if (OwnerActor == nullptr)
	{
		return;
	}

	AHUD* HUD = Cast<AHUD>(OwnerActor);
	
	if (HUD == nullptr)
	{
		return;
	}

	auto* PC = HUD->GetOwningPlayerController();

	if (PC == nullptr)
	{
		return;
	}
		
	if (WidgetClassMapping.Contains(InGameplayTag) == false)
	{
		return;
	}
	
	if (WidgetContainer.Contains(InGameplayTag) == false)
	{
		TSubclassOf<UUserWidget> WidgetClass = WidgetClassMapping[InGameplayTag];
		
		if (WidgetClass == nullptr)
		{
			return;
		}
		
		UUserWidget* InstanceWidget = CreateWidget<UUserWidget>(PC, WidgetClass->StaticClass());
		WidgetContainer.Emplace(InGameplayTag, InstanceWidget);
	}

	WidgetContainer[InGameplayTag]->RemoveFromParent();
}



