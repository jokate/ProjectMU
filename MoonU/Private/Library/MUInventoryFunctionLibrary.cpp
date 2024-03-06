// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/MUInventoryFunctionLibrary.h"

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

	return *DataManager->GetItemDataRow(InItemId);
}
