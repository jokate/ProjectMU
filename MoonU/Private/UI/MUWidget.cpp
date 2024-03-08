// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUWidget.h"

void UMUWidget::OnWidgetShow()
{
	OnWidgetShow_BP();
}

void UMUWidget::OnWidgetHide()
{
	OnWidgetHide_BP();
}

void UMUWidget::OnWidgetUpdated()
{
	OnWidgetUpdated_BP();
}

void UMUWidget::OnWidgetUpdatedByActor(AActor* InActor)
{
	OnWidgetUpdatedByActor_BP(InActor);
}

