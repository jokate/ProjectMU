// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enforcement/EnforcementHorizontalWidget.h"

#include "Components/HorizontalBox.h"
#include "UI/Enforcement/MUAttributeEnforceWidget.h"

void UEnforcementHorizontalWidget::InitializeWidget( int32 CharacterID,
                                                     FAttributeEnforcementSlotData& EnforcementWidgetData, TSubclassOf<UUserWidget> AttributeWidgetClass)
{
	if ( !IsValid(EnforcementHorizontal) )
	{
		return;
	}
	
	int32 MaximumCount = EnforcementWidgetData.WidgetCount;

	for ( int32 Index = 0; Index < MaximumCount; Index++ )
	{
		UMUAttributeEnforceWidget* AttributeEnforceWidget = CreateWidget<UMUAttributeEnforceWidget>(this, AttributeWidgetClass);

		if ( !IsValid( AttributeEnforceWidget ) )
		{
			continue;
		}
		
		EnforcementHorizontal->AddChildToHorizontalBox(AttributeEnforceWidget);
		
		FName SlotName = FName(*(FString::Printf(TEXT("%s_%d"), *EnforcementWidgetData.SlotName.ToString(), Index)));
		AttributeEnforceWidget->InitializeValue( CharacterID, SlotName);
		AttributeEnforceWidget->SetPadding( FMargin( PaddingValue ));
	}
}
