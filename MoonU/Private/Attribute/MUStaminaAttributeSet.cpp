// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/MUStaminaAttributeSet.h"

#include "GameplayEffectExtension.h"

UMUStaminaAttributeSet::UMUStaminaAttributeSet() :
	CurrentStamina(100.0f),
	MaxStamina(100.0f)
{
}

void UMUStaminaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

void UMUStaminaAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	constexpr float MinValue = 0.f;
	
	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		CurrentStamina = FMath::Clamp(GetCurrentStamina(), MinValue, GetMaxStamina());
	}

}
