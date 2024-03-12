// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/GameplayTagWidgetContainer.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"


// Sets default values for this component's propertiesa
UGameplayTagWidgetContainer::UGameplayTagWidgetContainer()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UUserWidget* UGameplayTagWidgetContainer::GetWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (CheckContainsWidget(InGameplayTag) == false)
	{
		return nullptr;
	}

	return WidgetContainer[InGameplayTag];
}

void UGameplayTagWidgetContainer::ShowWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (CheckContainsWidget(InGameplayTag) == false)
	{
		return;
	}
	
	UUserWidget* Widget = WidgetContainer[InGameplayTag];
	
	Widget->AddToViewport();

	if (auto* NeedToShow = Cast<IMUWidgetInterface>(Widget))
	{
		NeedToShow->OnWidgetShow();
	}
}

void UGameplayTagWidgetContainer::HideWidgetByGameplayTag(const FGameplayTag& InGameplayTag)
{
	if (CheckContainsWidget(InGameplayTag) == false)
	{
		return;
	}
	
	UUserWidget* Widget = WidgetContainer[InGameplayTag];
	if (auto* NeedToHide = Cast<IMUWidgetInterface>(Widget))
	{
		NeedToHide->OnWidgetHide();
	}
	Widget->RemoveFromParent();
}

bool UGameplayTagWidgetContainer::IsWidgetByGameplayTagInViewport(const FGameplayTag& InGameplayTag)
{
	if (WidgetContainer.Contains(InGameplayTag) == false)
	{
		return false;
	}

	return WidgetContainer[InGameplayTag]->IsInViewport();
}

bool UGameplayTagWidgetContainer::IsGameplayWidgetInViewport()
{
	bool bIsInViewport = false;
	for (const auto& Gameplay : GameplayTagForGameplay->WidgetGameplayTag)
	{
		bIsInViewport |= IsWidgetByGameplayTagInViewport(Gameplay);
	}

	return bIsInViewport;
}

void UGameplayTagWidgetContainer::HideAllWidgetForGameplay()
{
	for (const auto& Gameplay : GameplayTagForGameplay->WidgetGameplayTag)
	{
		HideWidgetByGameplayTag(Gameplay);
	}
}

const bool UGameplayTagWidgetContainer::CheckContainsWidget(const FGameplayTag& InGameplayTag)
{
	AActor* OwnerActor = GetOwner();

	if (OwnerActor == nullptr)
	{
		return false;
	}

	AHUD* HUD = Cast<AHUD>(OwnerActor);
	
	if (HUD == nullptr)
	{
		return false;
	}

	auto* PC = HUD->GetOwningPlayerController();

	if (PC == nullptr)
	{
		return false;
	}
		
	if (WidgetClassMapping.Contains(InGameplayTag) == false)
	{
		return false;
	}
	
	if (WidgetContainer.Contains(InGameplayTag) == false)
	{
		TSubclassOf<UUserWidget> WidgetClass = WidgetClassMapping[InGameplayTag];
		
		if (WidgetClass == nullptr)
		{
			return false;
		}
		
		UUserWidget* InstanceWidget = CreateWidget<UUserWidget>(PC, WidgetClass);
		WidgetContainer.Emplace(InGameplayTag, InstanceWidget);
	}

	return true;
}