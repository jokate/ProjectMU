// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUAttributeEnforceWidget.h"

#include "Data/MUPrimaryDataAsset.h"
#include "Singleton/MUEnforcementSubsystem.h"
#include "UI/Enforcement/EnforcementSelection/MUEnforcementSelectionCanvas.h"

void UMUAttributeEnforceWidget::InitializeValue(int32 InCharacterID,FName InSkillSlotName)
{
	AttributeSlotName = InSkillSlotName;
	CharacterID = InCharacterID;

	SetupWidgetInfo();
}

void UMUAttributeEnforceWidget::OnSelectionButtonClicked_Implementation()
{
	if ( OnAttributeSlotClicked.IsBound() == true )
	{
		OnAttributeSlotClicked.Broadcast(AttributeSlotName);
	}
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
