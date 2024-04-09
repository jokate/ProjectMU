// Fill out your copyright notice in the Description page of Project Settings.


#include "MUCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

UMUCharacterAttributeSet::UMUCharacterAttributeSet()
	: CurrentStamina(100.0f),
      MaxStamina(100.0f),
	  MaxCharge(100.0f),
	  ChargeInterval(20.0f)
{
	InitCurrentCharge(0.0f);
}

void UMUCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

bool UMUCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UMUCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinCharge = 0.0f;

	if (Data.EvaluatedData.Attribute == GetCurrentChargeAttribute())
	{
		CurrentCharge = FMath::Clamp(GetCurrentCharge(), MinCharge, GetMaxCharge());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		CurrentStamina = FMath::Clamp(GetCurrentStamina(), 0.0f, GetMaxStamina());
	}
}
