﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/StorageEntity.h"

#include "Components/InventoryComponent.h"
#include "Data/MUGameSettings.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "Interface/UI/Widget/MUWidgetInterface.h"


// Sets default values
AStorageEntity::AStorageEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
}

void AStorageEntity::OwnInventory(const FInventoryData& Item)
{
	InventoryComponent->OwnInventory(Item);
}

void AStorageEntity::OwnInventoryByIndex(const FInventoryData& Item, int32 Index)
{
	InventoryComponent->OwnInventoryByIndex(Item, Index);
}

void AStorageEntity::DisOwnInventory(const FInventoryData& Item)
{
	InventoryComponent->DisOwnInventory(Item);
}

void AStorageEntity::DisownInventoryByIndex(int32 Index)
{
	InventoryComponent->DisownInventoryByIndex(Index);
}

int32 AStorageEntity::GetMaxStorageAmount() const
{
	return InventoryComponent->GetMaxStorageAmount();
}

const TArray<FInventoryData>& AStorageEntity::GetTotalInventoryData()
{
	return InventoryComponent->GetTotalInventoryData();
}


