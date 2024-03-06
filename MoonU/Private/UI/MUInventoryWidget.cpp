// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUInventoryWidget.h"

void UMUInventoryWidget::OnInventoryUpdated()
{
	OnInventoryUpdated_BP();
}

void UMUInventoryWidget::OnWidgetShow()
{
	Super::OnWidgetShow();

	OnInventoryUpdated();
}
