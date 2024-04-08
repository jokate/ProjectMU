// Fill out your copyright notice in the Description page of Project Settings.


#include "MUCharacterAttributeSet.h"

UMUCharacterAttributeSet::UMUCharacterAttributeSet()
	: CurrentStamina(100.0f),
      MaxStamina(100.0f)
	
{
}

void UMUCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}
