// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TopMenu/MUTopMenuButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UMUTopMenuButton::InitializeWidget(FTopMenuItem InTopMenuItem)
{
	TopMenuItem = InTopMenuItem;

	if ( IsValid(TopMenuText) == true )
	{
		TopMenuText->SetText(TopMenuItem.TopMenuText);
	}

	
	if ( IsValid( TopMenuButton ) == true )
	{
		TopMenuButton->OnClicked.AddDynamic( this, &UMUTopMenuButton::OnClickedButtonCallback);
	}
}

void UMUTopMenuButton::OnClickedButtonCallback()
{
	if ( OnClickedButton.IsBound() == true )
	{
		OnClickedButton.Broadcast(TopMenuItem.ItemName);
	}	
}
