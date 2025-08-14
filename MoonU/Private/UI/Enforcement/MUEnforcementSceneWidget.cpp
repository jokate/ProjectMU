// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUEnforcementSceneWidget.h"
#include "UI/Enforcement/MUSkillTreeWidget.h"
#include "UI/Enforcement/EnforcementSelection/MUEnforcementSelectionCanvas.h"
#include "UI/TopMenu/MUTopMenuWidget.h"

void UMUEnforcementSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(SkillTreeWidget) == false || IsValid(MenuWidget) == false || IsValid(EnforcementSelectionWidget ) == false )
	{
		return;
	}

	MenuWidget->OnChangedTopMenu.AddDynamic( SkillTreeWidget, &UMUSkillTreeWidget::SetupCharacterID);
	MenuWidget->OnChangedTopMenu.AddDynamic( EnforcementSelectionWidget, &UMUEnforcementSelectionCanvas::UMUEnforcementSelectionCanvas::SetCharacterID);

	SkillTreeWidget->OnSkillTreeClicked.AddDynamic( this, &UMUEnforcementSceneWidget::SkillEnforcementClickedCallback);
	SkillTreeWidget->OnAttributeTreeClicked.AddDynamic(this, &UMUEnforcementSceneWidget::AttributeEnforcementClickedCallback);
}

void UMUEnforcementSceneWidget::AttributeEnforcementClickedCallback(FName SlotName)
{
	if ( IsValid(EnforcementSelectionWidget) == true )
	{
		EnforcementSelectionWidget->SetupAttribute(SlotName);
	}
}

void UMUEnforcementSceneWidget::SkillEnforcementClickedCallback(ESkillSlotType SlotType)
{
	if ( IsValid(EnforcementSelectionWidget) == true)
	{
		EnforcementSelectionWidget->SetupSkillAttribute(SlotType);
	}
}
