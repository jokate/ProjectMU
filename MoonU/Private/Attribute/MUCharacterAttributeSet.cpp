// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/MUCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

UMUCharacterAttributeSet::UMUCharacterAttributeSet()
	: CurrentStamina(100.0f),
      MaxStamina(100.0f),
	  CurrentTimeGauge(0.0f),
	  MaxTimeGauge(100.0f),
	  TimewindConsumption(0.25f)
{
}

void UMUCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetCurrentStaminaAttribute() || Attribute == GetCurrentTimeGaugeAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

void UMUCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

bool UMUCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UMUCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	constexpr float MinValue = 0.0f;

	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		CurrentStamina = FMath::Clamp(GetCurrentStamina(), MinValue, GetMaxStamina());
	}
}
