// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::OwnInventory(const FItemDataRow& Item, const int32 ItemAmount)
{
	UE_LOG(LogTemp, Log, TEXT("Own Inventory! : Item Id %d"), Item.ItemID);
}

void UInventoryComponent::DisOwnInventory(const FItemDataRow& Item, const int32 ItemAmount)
{
}
