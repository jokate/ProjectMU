// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Data/MUGameSettings.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "Blueprint/UserWidget.h"
#include "Library/MUFunctionLibrary.h"
#include "Library/MUInventoryFunctionLibrary.h"
#include "UI/MUInventoryWidget.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::OwnInventory(const FInventoryData& Item)
{
	FInventoryData InItem = Item;
	const auto& ItemData = UMUInventoryFunctionLibrary::GetItemDataRowById(Item.ItemID);

	if (InventoryData.Contains(InItem))
	{
		for (int32 i = InventoryData.Num() - 1; i >= 0; --i)
		{
			if (InItem.Amount <= 0)
			{
				break;
			}
			if (InItem == InventoryData[i])
			{
				if (InventoryData[i].Amount >= ItemData.ItemMaxAmount)
				{
					continue;
				}
				else
				{
					int32 ItemAmount = InventoryData[i].Amount + Item.Amount;

					if (ItemAmount > ItemData.ItemMaxAmount)
					{
						int32 ItemRemain = ItemAmount - ItemData.ItemMaxAmount;
						InItem.Amount = ItemRemain;
						InventoryData[i].Amount = ItemData.ItemMaxAmount;
					}
					else
					{
						InventoryData[i].Amount = ItemAmount;
						InItem.Amount = 0;
					}
				}
			}
		}
	}

	while(InItem.Amount > 0)
	{
		if (InItem.Amount > ItemData.ItemMaxAmount)
		{
			FInventoryData TempItem;
			
			TempItem.Amount = ItemData.ItemMaxAmount;
			TempItem.ItemID = InItem.ItemID;
			TempItem.UpgradeDatas = InItem.UpgradeDatas;
			
			InventoryData.Add(TempItem);

			InItem.Amount -= ItemData.ItemMaxAmount;
		}
		else
		{
			InventoryData.Add(InItem);
			InItem.Amount = 0;
		}
	}
	OnInventoryUpdated();
}

void UInventoryComponent::DisOwnInventory(const FInventoryData& Item)
{
	const auto& ItemData = UMUInventoryFunctionLibrary::GetItemDataRowById(Item.ItemID);

	OnInventoryUpdated();
}

int32 UInventoryComponent::GetMaxStorageAmount() const
{
	return MaxInventoryAmount;
}

const TArray<FInventoryData>& UInventoryComponent::GetTotalInventoryData()
{
	return InventoryData;
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

