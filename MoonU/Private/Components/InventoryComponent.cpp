﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Data/MUGameSettings.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "Blueprint/UserWidget.h"
#include "UI/MUInventoryWidget.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::OwnInventory(const FInventoryData& Item, const int32 ItemAmount)
{
	if (InventoryAmount.Contains(Item))
	{
		InventoryAmount[Item] += ItemAmount;
		return;
	}

	InventoryAmount.Add(Item, ItemAmount);
	OnInventoryUpdated();
}

void UInventoryComponent::DisOwnInventory(const FInventoryData& Item, const int32 ItemAmount)
{
	if (InventoryAmount.Contains(Item))
	{
		InventoryAmount[Item] -= ItemAmount;

		if (InventoryAmount[Item] <= 0)
		{
			InventoryAmount.Remove(Item);
		}
	}
	OnInventoryUpdated();
}

int32 UInventoryComponent::GetMaxStorageAmount() const
{
	return MaxInventoryAmount;
}

const TMap<FInventoryData, int32>& UInventoryComponent::GetTotalInventoryData()
{
	return InventoryAmount;
}

void UInventoryComponent::OnInventoryUpdated()
{
	const auto* GameSettings = UMUGameSettings::Get();
	if (GameSettings == nullptr)
	{
		return;
	}
	
	if (auto* TagWidgetOwner = GetOwner<IGameplayTagWidgetOwner>())
	{
		UUserWidget* Widget =TagWidgetOwner->GetWidgetByGameplayTag(GameSettings->InventoryUITag);

		if (Widget == nullptr)
		{
			return;
		}

		if (auto* MUWidget = Cast<IMUWidgetInterface>(Widget))
		{
			MUWidget->OnWidgetUpdated();
		}
	}
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

