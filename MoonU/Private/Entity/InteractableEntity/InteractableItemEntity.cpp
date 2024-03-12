// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/InteractableItemEntity.h"

#include "Data/MUGameSettings.h"
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

	if (bIsLootingItem)
	{
		MakeItemInfo();
	}
}

void AInteractableItemEntity::MakeItemInfo()
{
	const auto* GS = UMUGameSettings::Get();
	if (GS == nullptr)
	{
		return;
	}
	
	const FItemPoolStructRow ItemRow = UMUInventoryFunctionLibrary::GetItemPoolRow(ItemLootingName);

	for (const auto& ItemPool : ItemRow.ItemPoolingData)
	{
		const FItemDropData& DropData = ItemPool.Value;
		const float RandomVal = FMath::RandRange(0.0f, 1.0f);
		if (RandomVal <= DropData.Percentage)
		{
			for (const auto& DropPool : DropData.DropPools)
			{
				const FItemDataRow& ItemData = UMUInventoryFunctionLibrary::GetItemDataRow(DropPool.ItemName);
				FInventoryData InvData;
				InvData.ItemID = ItemData.ItemID;

				const int32 Value = FMath::RandRange(DropPool.MinAmount, DropPool.MaxAmount);
				
				InvData.Amount = Value;

				InventoryData.Emplace(InvData);
			}
		}
	}
}

void AInteractableItemEntity::OnInteracted(AActor* InstigatorActor)
{
	Super::OnInteracted(InstigatorActor);

	auto* InventoryOwner = Cast<IInventoryOwner>(InstigatorActor);

	if (InventoryOwner == nullptr)
	{
		return;
	}

	for (const auto& Inventory : InventoryData)
	{
		InventoryOwner->OwnInventory(Inventory);
	}
	
}


