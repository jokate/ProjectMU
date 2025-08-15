// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUSkillSlotWidget.h"

#include "Components/MUEnforcementManageComponent.h"
#include "Data/MUPrimaryDataAsset.h"
#include "Library/MUFunctionLibrary.h"
#include "Singleton/MUEnforcementSubsystem.h"
#include "UI/Enforcement/EnforcementSelection/MUEnforcementSelectionCanvas.h"

void UMUSkillSlotWidget::InitializeSkillSlot(int32 InCharacterID, ESkillSlotType InSkillSlot)
{
	CharacterID = InCharacterID;
	SkillSlotType = InSkillSlot;

	SetupWidgetInfo();
}

void UMUSkillSlotWidget::OnSelectionButtonClicked_Implementation()
{
	// 스킬 강화에 대한 부분을 끌고 와야 함.
	// -> 별도 데이터 관리가 필요한 부분인지 여부 체크 필요. ( 사실 Drop 쪽에 모두 넣어버리면 되기는 한데... )
	if (OnSkillSlotClicked.IsBound() == true)
	{
		OnSkillSlotClicked.Broadcast(SkillSlotType);
	}
}

void UMUSkillSlotWidget::SetupWidgetInfo()
{
	UMUEnforcementManageComponent* EnforcementManageComponent = UMUFunctionLibrary::GetEnforcementManageComponent( this );
	
	if ( IsValid( EnforcementManageComponent ) == true )
	{
		int32 TempAllocatedEnforcement = EnforcementManageComponent->GetAllocatedSkill(CharacterID, SkillSlotType);

		AllocatedEnforcementID = TempAllocatedEnforcement;
	}
	
	Super::SetupWidgetInfo();
}
