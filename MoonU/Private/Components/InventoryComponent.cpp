// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "MUDefines.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Data/Item/MUItemData.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	IAbilitySystemInterface* ASI = GetOwner<IAbilitySystemInterface>();

	if (ASI == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

	if (ASC == nullptr)
	{
		return;
	}

	const UMUCharacterAttributeSet* AttributeSet = ASC->GetSet<UMUCharacterAttributeSet>();

	if (AttributeSet == nullptr)
	{
		return;
	}

	const int32 ItemMaxAmount = AttributeSet->GetItemMaxAmount();
	InventorySlots.Init(FInventorySlotData(), ItemMaxAmount);
}

void UInventoryComponent::UseItem(int32 SlotIndex)
{
	if (InventorySlots.IsValidIndex(SlotIndex)) 
	{
		FInventorySlotData SlotData = InventorySlots[SlotIndex];
		if (SlotData.ItemID != EMPTY_ID && SlotData.ItemAmount != EMPTY_AMOUNT)
		{
			FGameplayEventData EventData;
			EventData.EventMagnitude = InventorySlots[SlotIndex].ItemID;
		}
	}
}

void UInventoryComponent::AddItem(int32 ItemId, int32 ItemAmount)
{
	int32 TempAmount = ItemAmount;
	
	for (const auto& InventorySlot : InventorySlots)
	{
		if (InventorySlot.ItemID == ItemId )
		{
			
		}	
	}
}



