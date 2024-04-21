// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/MUCharacterAttributeSetBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "MUDefines.h"
#include "Elements/Framework/TypedElementOwnerStore.h"
#include "Perception/AISense_Damage.h"

UMUCharacterAttributeSetBase::UMUCharacterAttributeSetBase()
	: Damage(0.0f),
      MaxHp(100.0f),
	  DefendRange(300.0f),
	  AttackRange(150.0f)
{
	InitCurrentHp(GetMaxHp());
}

void UMUCharacterAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

bool UMUCharacterAttributeSetBase::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude > 0.0f)
		{
			if (Data.Target.HasMatchingGameplayTag(MU_CHARACTERSTATE_DODGE))
			{
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}
		}
	}

	return true;
}

void UMUCharacterAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const float MinHealth = 0.f;
	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		SetCurrentHp(FMath::Clamp(GetCurrentHp(), MinHealth, GetMaxHp()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetCurrentHp(FMath::Clamp(GetCurrentHp() - GetDamage(),  MinHealth, GetMaxHp()));
		SetDamage(0);
	}

	if (GetCurrentHp() <= 0.0f && !bOutOfHealth)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningAbilitySystemComponent()->GetAvatarActor(), MU_CHARACTERSTATE_DEAD, FGameplayEventData());
	}

	bOutOfHealth = (GetCurrentHp() <= 0.0f);
}
