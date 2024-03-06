﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/InteractableItemEntity.h"

#include "Interface/InventoryOwner.h"
#include "Library/MUInventoryFunctionLibrary.h"


// Sets default values
AInteractableItemEntity::AInteractableItemEntity()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void AInteractableItemEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableItemEntity::OnInteracted(AActor* InstigatorActor)
{
	Super::OnInteracted(InstigatorActor);

	auto* InventoryOwner = Cast<IInventoryOwner>(InstigatorActor);

	if (InventoryOwner == nullptr)
	{
		return;
	}

	const FItemDataRow& ItemData = UMUInventoryFunctionLibrary::GetItemDataRow(ItemEntityName);

	if (ItemData.ItemName == NAME_None)
	{
		return;
	}
	
	InventoryOwner->OwnInventory(ItemData, 1);
}


