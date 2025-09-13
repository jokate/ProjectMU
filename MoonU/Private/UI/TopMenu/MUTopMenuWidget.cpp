// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TopMenu/MUTopMenuWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Library/MUFunctionLibrary.h"
#include "UI/TopMenu/MUTopMenuButton.h"

void UMUTopMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if ( IsValid( TopMenuHorizontalBox ) == false )
	{
		return;
	}

	TopMenuHorizontalBox->ClearChildren();
	
	FTopMenuData WidgetData;
	if ( UMUFunctionLibrary::GetTopMenuWidgetData(this, TopMenuName, WidgetData) == false )
	{
		return;
	}

	for ( FTopMenuItem& ItemName : WidgetData.ItemNames )
	{
		UMUTopMenuButton* TopMenuButton = CreateWidget<UMUTopMenuButton>(this, WidgetData.ItemWidgetClass );

		if ( IsValid( TopMenuButton ) == false )
		{
			continue;
		}

		TopMenuHorizontalBox->AddChildToHorizontalBox(TopMenuButton);
		
		TopMenuButton->SetPadding( PaddingValue);
		TopMenuButton->InitializeWidget(ItemName);
		TopMenuButton->OnClickedButton.AddDynamic( this, &UMUTopMenuWidget::OnTopMenuChanged);
	}
}

void UMUTopMenuWidget::OnTopMenuChanged(FName InName)
{
	if (OnChangedTopMenu.IsBound() == true)
	{
		OnChangedTopMenu.Broadcast(InName);
	}
}
