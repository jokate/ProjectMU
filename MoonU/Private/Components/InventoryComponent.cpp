// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "MUDefines.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Data/Item/MUItemData.h"
#include "Singleton/GameDataManager.h"


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
	UGameDataManager* GDM = UGameDataManager::Get();

	if (GDM == nullptr)
	{
		return;
	}

	FItemDataRow ItemData = GDM->GetItemDataRow(ItemId);
	
	if (ItemData.ItemID == 0)
	{
		return;
	}
	
	int32 TempAmount = ItemAmount;
	
	for (auto& InventorySlot : InventorySlots)
	{
		bool bRemainItem = InventorySlot.ItemID == ItemId;
		bRemainItem &= ItemData.ItemMaxAmount > InventorySlot.ItemAmount;
		if (bRemainItem) 
		{
			//해당 슬롯에 꽉차기까지 필요한 개수는 NeedAmount
			int32 NeedAmount = 	ItemData.ItemMaxAmount - InventorySlot.ItemAmount;

			//만약에 필요개수가 현재 있는 아이템의 개수보다 더 많다고 한다면?
			if (NeedAmount > TempAmount)
			{
				InventorySlot.ItemAmount += TempAmount;
			}
			else
			{
				// 만약 필요 개수보다 현재 아이템의 개수가 많다면?
				InventorySlot.ItemAmount += NeedAmount;
				TempAmount -= NeedAmount;
			}
		}	
	}

	if (TempAmount > 0)
	{
		int32 Index = InventorySlots.Find(FInventorySlotData());

		if (Index != INDEX_NONE)
		{
			InventorySlots[Index].ItemAmount = TempAmount;
			InventorySlots[Index].ItemID = ItemId;
 		}
	}
}



