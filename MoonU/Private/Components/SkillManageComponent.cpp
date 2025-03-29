// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkillManageComponent.h"


// Sets default values for this component's properties
USkillManageComponent::USkillManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USkillManageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USkillManageComponent::AddSkillSlot(ESkillSlotType SkillSlotType, FName SkillID)
{
	AllocatedSkillID.Add(SkillSlotType, SkillID);

	if ( OnSkillUpdated.IsBound() == true )
	{
		OnSkillUpdated.Broadcast();
	}
}

void USkillManageComponent::RemoveSkillSLot(ESkillSlotType SkillSlotType)
{
	AllocatedSkillID.Remove(SkillSlotType);
	if ( OnSkillUpdated.IsBound() == true )
	{
		OnSkillUpdated.Broadcast();
	}
}

const FName USkillManageComponent::GetSkillIDBySlot(ESkillSlotType SkillSlot)
{
	if ( AllocatedSkillID.Contains(SkillSlot) == false )
	{
		return FName();
	}

	return AllocatedSkillID[SkillSlot];
}