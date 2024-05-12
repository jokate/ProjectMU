// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton/GameDataManager.h"

#include "Data/Item/MUItemData.h"
#include "EnvironmentQuery/EnvQueryDebugHelpers.h"

void UGameDataManager::PostLoad()
{
	UObject::PostLoad();

	if (ItemDataTable != nullptr)
	{
		TArray<FName> RowNames = ItemDataTable->GetRowNames();
		for (const auto& RowName : RowNames)
		{
			FItemDataRow* Item = ItemDataTable->FindRow<FItemDataRow>(RowName, "");
			if (Item->ItemID == 0)
			{
				Item->ItemID = GetTypeHash(Item->ItemName);
				ItemDataTable->AddRow(RowName, *Item);
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

const FItemDataRow UGameDataManager::GetItemDataRow(const FName& InNameId) const
{
	const FItemDataRow* Row = ItemDataTable->FindRow<FItemDataRow>(InNameId, "");

	if (Row == nullptr)
	{
		return FItemDataRow();
	}

	return *Row;
}

const FItemDataRow UGameDataManager::GetItemDataRow(const int32 InItemId)
{
	if (ItemTableMap.Contains(InItemId) == false)
	{
		return FItemDataRow();
	}

	const FItemDataRow* Row = ItemDataTable->FindRow<FItemDataRow>(ItemTableMap[InItemId], "");

	if (Row == nullptr)
	{
		return FItemDataRow();
	}

	return *Row;
}
