// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUSkillSlotWidget.h"

#include "Interface/SkillManager.h"

void UMUSkillSlotWidget::AllocateSkillID(FName SkillID)
{
	APawn* OwnerPawn = GetOwningPlayerPawn();

	if ( IsValid(OwnerPawn) == false )
	{
		return;
	}

	ISkillManager* SkillManager = Cast<ISkillManager>(OwnerPawn);

	if ( SkillManager == nullptr )
	{
		return;
	}

	SkillManager->AddSkillSlot(SkillSlotType, SkillID);
}

bool UMUSkillSlotWidget::GetSkillIDForSlot( FName& SkillID ) const
{
	APawn* OwnerPawn = GetOwningPlayerPawn();

	if ( IsValid(OwnerPawn) == false )
	{
		return false;
	}

	ISkillManager* SkillManager = Cast<ISkillManager>(OwnerPawn);

	if ( SkillManager == nullptr )
	{
		return false;
	}

	SkillID = SkillManager->GetSkillIDBySlot(SkillSlotType);
	return true;
 }
