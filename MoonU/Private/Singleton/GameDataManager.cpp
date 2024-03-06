﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/GameDataManager.h"

#include "Data/Item/MUItemData.h"

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
