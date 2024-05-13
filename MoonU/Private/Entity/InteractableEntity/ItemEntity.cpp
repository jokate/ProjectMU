// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/ItemEntity.h"

#include "Interface/InventoryOwner.h"
#include "Singleton/GameDataManager.h"


// Sets default values
AItemEntity::AItemEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AItemEntity::OnInitialize(const FName& InName)
{
	UGameDataManager* GDM = UGameDataManager::Get();

	if (GDM == nullptr)
	{
		return;
	}

	float Percentage = FMath::RandRange(0.0, 1.0);
	
	FItemDropTableRow DropTableRow = GDM->GetItemDropTableRow(InName);

	for (auto& DropData : DropTableRow.DropData)
	{
		if (DropData.Percentage > Percentage)
		{
			for (const auto& DropPool : DropData.DropPools)
			{
				FInventorySlotData SlotData;
				FItemDataRow ItemDataRow = GDM->GetItemDataRow(DropPool.ItemName);
				int32 RandNum = FMath::RandRange(DropPool.MinAmount, DropPool.MaxAmount);
				SlotData.ItemAmount = RandNum;
				SlotData.ItemID = ItemDataRow.ItemID;

				InventorySlotData.Emplace(SlotData);
			}
		}
	}
}

// Called when the game starts or when spawned
void AItemEntity::BeginPlay()
{
	Super::BeginPlay();
}