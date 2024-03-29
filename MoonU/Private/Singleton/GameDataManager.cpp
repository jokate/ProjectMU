﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/GameDataManager.h"

#include "Data/Item/MUItemData.h"
#include "EnvironmentQuery/EnvQueryDebugHelpers.h"

void UGameDataManager::PostLoad()
{
	UObject::PostLoad();

	if (ItemTable != nullptr)
	{
		TArray<FName> RowNames = ItemTable->GetRowNames();
		for (const auto& RowName : RowNames)
		{
			FItemDataRow* Item = ItemTable->FindRow<FItemDataRow>(RowName, "");
			if (Item->ItemID == 0)
			{
				Item->ItemID = GetTypeHash(Item->ItemName);
				ItemTable->AddRow(RowName, *Item);
			}

			ItemTableMap.Add(Item->ItemID, RowName);
		}
	}
	
}

UGameDataManager* UGameDataManager::Get()
{
	UGameDataManager* Singleton = CastChecked<UGameDataManager>(GEngine->GameSingleton);

	if (Singleton)
	{
		return Singleton;
	}

	return NewObject<UGameDataManager>();
}

const FItemDataRow* UGameDataManager::GetItemDataRow(const FName& InNameId) const
{
	const FItemDataRow* Item = ItemTable->FindRow<FItemDataRow>(InNameId, "");
	return Item;
}

const FItemDataRow* UGameDataManager::GetItemDataRow(const int32 ItemId) const
{
	if (ItemTableMap.Contains(ItemId) == false)
	{
		return nullptr;
	}

	const FItemDataRow* Item = ItemTable->FindRow<FItemDataRow>(ItemTableMap[ItemId], "");
	
	return Item;
}

const FItemPoolStructRow* UGameDataManager::GetItemPoolRow(const FName& PoolName) const
{
	const FItemPoolStructRow* Row = ItemPoolTable->FindRow<FItemPoolStructRow>(PoolName, "");

	if (Row == nullptr)
	{
		return nullptr;
	}

	return Row;
}

const FCraftDataRow* UGameDataManager::GetCraftDataRow(const FName& CraftItemName) const
{
	const FCraftDataRow* Row = CraftItemTable->FindRow<FCraftDataRow>(CraftItemName, "");

	if (Row == nullptr)
	{
		return nullptr;
	}

	return Row;
}

