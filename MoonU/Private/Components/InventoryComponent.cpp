// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"


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
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

