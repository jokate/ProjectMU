// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MUWidgetComponent.h"

#include "UI/MUGASWidget.h"


// Sets default values for this component's properties
UMUWidgetComponent::UMUWidgetComponent()
{
}

void UMUWidgetComponent::InitWidget()
{
	Super::InitWidget();
	
	UMUGASWidget* MUWidget = Cast<UMUGASWidget>(GetWidget());
	
	if (MUWidget)
	{
		MUWidget->SetAbilitySystemComponent(GetOwner());
	}
}



