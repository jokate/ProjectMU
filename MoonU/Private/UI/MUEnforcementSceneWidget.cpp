// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUEnforcementSceneWidget.h"
#include "UI/MUSkillTreeWidget.h"
#include "UI/TopMenu/MUTopMenuWidget.h"

void UMUEnforcementSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(SkillTreeWidget) == false || IsValid(MenuWidget) == false )
	{
		return;
	}

	MenuWidget->OnChangedTopMenu.AddDynamic( SkillTreeWidget, &UMUSkillTreeWidget::UMUSkillTreeWidget::SetupCharacterID);
}
