// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/MUCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MUDefines.h"

UMUCharacterAttributeSet::UMUCharacterAttributeSet()
	: MaxExperience(100.f),
	  CurrentExperience(0.f)
{
}

void UMUCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UMUCharacterAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{ 
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	constexpr float MinValue = 0.f;
	
	if (Attribute == GetCurrentExperienceAttribute())
	{
		//만약 레벨업이 되었다면 0으로 만든다.
		if (CurrentExperience.GetCurrentValue() == GetMaxExperience())
		{
			CurrentExperience = MinValue;
			Level = GetLevel() + 1; 
			
			UE_LOG(LogTemp, Log, TEXT("LevelUp"));

			//레벨업에 대한 피드백을 보인다.
			//시간을 멈추고 + 강화 선택지를 준다던지
			//-> 이거는 이벤트를 기반으로 설계되게끔
			
		}
	}
}

bool UMUCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UMUCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	constexpr float MinValue = 0.0f;
	
	// 경험치 Attribute에 대한 처리.
	if (Data.EvaluatedData.Attribute == GetCurrentExperienceAttribute())
	{
		CurrentExperience = FMath::Clamp(GetCurrentExperience(), MinValue, GetMaxExperience());
		UE_LOG(LogTemp, Log, TEXT("Current Exp : %f"), CurrentExperience.GetCurrentValue());
	}
}
