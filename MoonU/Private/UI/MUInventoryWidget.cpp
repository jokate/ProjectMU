﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUInventoryWidget.h"

void UMUInventoryWidget::OnWidgetShow()
{
	Super::OnWidgetShow();
	OnWidgetUpdated_BP();
}
