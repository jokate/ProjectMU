// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUSkillSlotWidget.h"

#include "Interface/SkillManager.h"

/*void UMUSkillSlotWidget::AllocateSkillID(FName SkillID)
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
 }*/

void UMUSkillSlotWidget::OnSelectionButtonClicked_Implementation()
{
	Super::OnSelectionButtonClicked_Implementation();
	// 스킬 강화에 대한 부분을 끌고 와야 함.
	// -> 별도 데이터 관리가 필요한 부분인지 여부 체크 필요. ( 사실 Drop 쪽에 모두 넣어버리면 되기는 한데... )

	
}
