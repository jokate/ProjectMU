// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUAttributeEnforceWidget.h"

#include "Components/MUEnforcementManageComponent.h"
#include "Data/MUPrimaryDataAsset.h"
#include "Library/MUFunctionLibrary.h"
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
	UMUEnforcementManageComponent* EnforcementManageComponent = UMUFunctionLibrary::GetEnforcementManageComponent( this );

	if ( IsValid( EnforcementManageComponent ) == true )
	{
		int32 TempAllocatedEnforcement = EnforcementManageComponent->GetAllocatedAttribute(CharacterID, AttributeSlotName);

		AllocatedEnforcementID = TempAllocatedEnforcement;
	}
	
	Super::SetupWidgetInfo();
}
