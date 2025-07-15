// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/MUTimewinderAttribute.h"

#include "GameplayEffectExtension.h"

UMUTimewinderAttribute::UMUTimewinderAttribute() :
	CurrentTimeGauge(0.0f),
	MaxTimeGauge(100.0f),
	TimewindConsumption(0.1f),
	TimeStopConsumption(50.0f),
	TimeStopDuration(3.0f)
{
}

void UMUTimewinderAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	constexpr float MinValue = 0.f;
		
	if (Data.EvaluatedData.Attribute == GetCurrentTimeGaugeAttribute())
	{
		CurrentTimeGauge = FMath::Clamp(GetCurrentTimeGauge(), MinValue, GetMaxTimeGauge());	
	}
}

void UMUTimewinderAttribute::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UMUTimewinderAttribute::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetCurrentTimeGaugeAttribute())
	{
		NewValue = FMath::Clamp( NewValue, 0.0f, GetMaxTimeGauge() );
	}
}
