// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentComponent.h"

#include "Interface/Equippable.h"

void UEquipmentComponent::EquipItem(AActor* InActor)
{
}

const FGameplayTag UEquipmentComponent::GetEquippingItemTag()
{
	if (EquipmentActor == nullptr)
	{
		return FGameplayTag();
	}

	auto* EquippableEntity = Cast<IEquippable>(EquipmentActor);

	if (EquippableEntity == nullptr)
	{
		return FGameplayTag();
	}

	return EquippableEntity->GetEquipEntityTag();
}
