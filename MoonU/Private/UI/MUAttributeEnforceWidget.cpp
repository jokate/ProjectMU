// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUAttributeEnforceWidget.h"

#include "Singleton/MUEnforcementSubsystem.h"

void UMUAttributeEnforceWidget::InitializeValue(int32 InCharacterID,FName InSkillSlotName)
{
	AttributeSlotName = InSkillSlotName;
	CharacterID = InCharacterID;

	SetupWidgetInfo();
}

void UMUAttributeEnforceWidget::SetupWidgetInfo()
{
	const APlayerController* PC = GetOwningPlayer();

	if ( IsValid( PC ) == false )
	{
		return;
	}

	UMUEnforcementSubsystem* EnforcementSubsystem = ULocalPlayer::GetSubsystem<UMUEnforcementSubsystem>(PC->GetLocalPlayer());

	if ( IsValid( EnforcementSubsystem ) == true )
	{
		int32 TempAllocatedEnforcement = EnforcementSubsystem->GetAllocatedAttribute(CharacterID, AttributeSlotName);

		AllocatedEnforcementID = TempAllocatedEnforcement;
	}
	
	Super::SetupWidgetInfo();
}
