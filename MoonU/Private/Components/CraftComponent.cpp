// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CraftComponent.h"

#include "IDetailTreeNode.h"
#include "Interface/InventoryOwner.h"
#include "Library/MUInventoryFunctionLibrary.h"


// Sets default values for this component's properties
UCraftComponent::UCraftComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCraftComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool UCraftComponent::CanCraftItem(const FName& CraftItemName, const int32 Amount)
{
	auto* InventoryOwner = GetOwner<IInventoryOwner>();

	if (InventoryOwner == nullptr)
	{
		return false;
	}

	const TArray<FInventoryData>& InventoryDatas = InventoryOwner->GetTotalInventoryData();

	const auto& CraftItemData = UMUInventoryFunctionLibrary::GetCraftItemData(CraftItemName); 
	
	for (const auto& NeedItems : CraftItemData.NeedItemsToCraft)
	{
		const auto& ItemData = UMUInventoryFunctionLibrary::GetItemDataRow(NeedItems.ItemName);

		if (InventoryDatas.Contains(ItemData.ItemID) == false)
		{
			return false;
		}

		bool bIsSatisfied = false;
		
		for (const auto& InventoryData : InventoryDatas)
		{
			bool bIsInventoryValid = InventoryData.ItemID == ItemData.ItemID;
			bIsInventoryValid &= InventoryData.Amount >= NeedItems.NeedAmount;
			if (bIsInventoryValid)
			{
				bIsSatisfied = true;
			}
		}

		if (bIsSatisfied == false)
		{
			return false;
		}
	}

	return true;
}

void UCraftComponent::CraftItem(const FName& CraftItemName, const int32 Amount)
{
	auto* InventoryOwner = GetOwner<IInventoryOwner>();

	if (InventoryOwner == nullptr)
	{
		return;
	}
	
	if (CanCraftItem(CraftItemName, Amount))
	{
		const auto& CraftItemData = UMUInventoryFunctionLibrary::GetCraftItemData(CraftItemName);

		for (const auto& NeedItem : CraftItemData.NeedItemsToCraft)
		{
			const auto& NeedItemData = UMUInventoryFunctionLibrary::GetItemDataRow(NeedItem.ItemName);
			const FInventoryData InventoryData(NeedItemData.ItemID, NeedItem.NeedAmount);
			InventoryOwner->DisOwnInventory(InventoryData);
		}
		
		const auto& ItemData = UMUInventoryFunctionLibrary::GetItemDataRow(CraftItemName);

		const FInventoryData InventoryData(ItemData.ItemID, Amount);

		InventoryOwner->OwnInventory(InventoryData);
	}
}



