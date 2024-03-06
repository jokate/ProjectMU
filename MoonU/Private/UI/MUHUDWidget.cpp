// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUHUDWidget.h"

void UMUHUDWidget::OnOxygenChanged(float InOxygen)
{
	OnOxygenChanged_BP(InOxygen);
}

void UMUHUDWidget::OnStaminaChanged(float InStamina)
{
	OnStaminaChanged_BP(InStamina);
}

void UMUHUDWidget::OnInteratableObjectInBound(AActor* InteractableActor)
{
	OnInteratableObjectInBound_BP(InteractableActor);
}
