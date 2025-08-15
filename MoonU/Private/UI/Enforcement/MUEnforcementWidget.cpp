// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/MUEnforcementWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MUEnforcementManageComponent.h"
#include "Library/MUFunctionLibrary.h"

void UMUEnforcementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid(SelectionButton) == true )
	{
		SelectionButton->OnClicked.AddDynamic( this, &UMUEnforcementWidget::OnSelectionButtonClicked );
	}

	UMUEnforcementManageComponent* ManagerComponent = UMUFunctionLibrary::GetEnforcementManageComponent( this );

	if ( IsValid(ManagerComponent) == true )
	{
		ManagerComponent->OnEnforcementUpdated.AddDynamic( this, &UMUEnforcementWidget::SetupWidgetInfo);
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
