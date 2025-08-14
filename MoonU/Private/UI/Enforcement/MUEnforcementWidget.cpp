// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUEnforcementWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Library/MUFunctionLibrary.h"

void UMUEnforcementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(SelectionButton) == true )
	{
		SelectionButton->OnClicked.AddDynamic( this, &UMUEnforcementWidget::OnSelectionButtonClicked );
	}
}

void UMUEnforcementWidget::SetupWidgetInfo()
{
	FMUEnforcementData EnforcementData;
	if ( UMUFunctionLibrary::GetEnforcementData(this, AllocatedEnforcementID, EnforcementData) == true )
	{
		PortraitImage->SetBrushFromTexture(EnforcementData.DescriptionIcon);
	} 
}
