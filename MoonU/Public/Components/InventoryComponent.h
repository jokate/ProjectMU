// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/InventoryOwner.h"
#include "InventoryComponent.generated.h"


struct FInventorySlotData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UInventoryComponent : public UActorComponent, public IInventoryOwner
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	virtual void UseItemBySlot(int32 SlotIndex) override;

	virtual void UseItemByItemID(int32 ItemID) override;

	virtual void AddItem(int32 ItemId, int32 ItemAmount) override;

	void UseItem(FInventorySlotData& SlotData, class UAbilitySystemComponent* ASC);  

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	TArray<FInventorySlotData> InventorySlots;
};
