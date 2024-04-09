// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MUGASWidget.h"
#include "AbilitySystemBlueprintLibrary.h"

void UMUGASWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	if (IsValid(InOwner))
	{
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
	}
}

UAbilitySystemComponent* UMUGASWidget::GetAbilitySystemComponent() const
{
	return ASC;
}
