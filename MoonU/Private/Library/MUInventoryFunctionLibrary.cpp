// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUInventoryFunctionLibrary.h"

#include "Interface/InventoryOwner.h"
#include "Singleton/GameDataManager.h"

const FItemDataRow UMUInventoryFunctionLibrary::GetItemDataRow(const FName& InItemId)
{
	const auto* DataManager = UGameDataManager::Get();

	if (DataManager == nullptr)
	{
		return FItemDataRow();
	}

	return *DataManager->GetItemDataRow(InItemId);
}

const FItemDataRow UMUInventoryFunctionLibrary::GetItemDataRowById(const int32 InItemId)
{
	const auto* DataManager = UGameDataManager::Get();

	if (DataManager == nullptr)
	{
		return FItemDataRow();
	}
	
	if (InItemId == 0)
	{
		return FItemDataRow();
	}
	return *DataManager->GetItemDataRow(InItemId);
}

const FItemPoolStructRow UMUInventoryFunctionLibrary::GetItemPoolRow(const FName& InPoolId)
{
	const auto* DataManager = UGameDataManager::Get();

	if (DataManager == nullptr)
	{
		return FItemPoolStructRow();
	}

	return *DataManager->GetItemPoolRow(InPoolId);
}

const FCraftDataRow UMUInventoryFunctionLibrary::GetCraftItemData(const FName& InItemId)
{
	const auto* DataManager = UGameDataManager::Get();

	if (DataManager == nullptr)
	{
		return FCraftDataRow();
	}
	
	return *DataManager->GetCraftDataRow(InItemId);
}

void UMUInventoryFunctionLibrary::MoveItemToTargetIndex(AActor* OwnerActor, AActor* TargetActor, int32 StartIndex,
                                                        int32 TargetIndex)
{
	auto* ItemOwner = Cast<IInventoryOwner>(OwnerActor);

	if (ItemOwner == nullptr)
	{
		return;
	}

	auto* TargetInventoryOwner = Cast<IInventoryOwner>(TargetActor);

	if (TargetInventoryOwner == nullptr)
	{
		return;
	}

	const TArray<FInventoryData> OwnerInventoryData = ItemOwner->GetTotalInventoryData();
	const TArray<FInventoryData> TargetInventoryData = TargetInventoryOwner->GetTotalInventoryData();

	const FInventoryData& OwnerInvData = OwnerInventoryData[StartIndex];
	const FInventoryData& TargetInvData = TargetInventoryData[TargetIndex];

	TargetInventoryOwner->OwnInventoryByIndex(OwnerInvData, TargetIndex);
	ItemOwner->OwnInventoryByIndex(TargetInvData, StartIndex);
}

void UMUInventoryFunctionLibrary::OwnInventoryItem(AActor* TargetActor, int32 ItemID, int32 Amount)
{
	auto* InventoryOwner = Cast<IInventoryOwner>(TargetActor);

	if (InventoryOwner == nullptr)
	{
		return;
	}

	const FInventoryData InventoryData(ItemID, Amount);

	InventoryOwner->OwnInventory(InventoryData);
}

void UMUInventoryFunctionLibrary::DisownInventoryItem(AActor* TargetActor, int32 ItemID, int32 Amount)
{
	auto* InventoryOwner = Cast<IInventoryOwner>(TargetActor);

	if (InventoryOwner == nullptr)
	{
		return;
	}

	const FInventoryData InventoryData(ItemID, Amount);

	InventoryOwner->DisOwnInventory(InventoryData);
}
