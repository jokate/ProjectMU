// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/MUCharacterAttributeSetBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "MUDefines.h"

UMUCharacterAttributeSetBase::UMUCharacterAttributeSetBase()
	: Damage(0.0f),
      MaxHp(100.0f),
	  DefendRange(300.0f),
	  AttackRange(150.0f),
	  AttackDamage(10.0f),
	  DefendRate(0.5f),
	  DropExperience(0.f)
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

void UMUCharacterAttributeSetBase::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	HandleHPAttributeChange( Attribute, OldValue, NewValue );
}

bool UMUCharacterAttributeSetBase::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	bool bResult = HandlePreDamage(Data);

	return bResult;
}

void UMUCharacterAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//GE로 Attribute가 변환된 경우.
	HandleHPGameplayEffectCallback(Data);
	
	CheckDeath( Data );
}

void UMUCharacterAttributeSetBase::HandleHPAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
	float NewValue)
{
	// Attribute엗에 대한 성.
	if (Attribute == GetCurrentHpAttribute()) 
	{
		if (bOutOfHealth && NewValue > 0.0f)
		{
			// Regenerated -> Ability 수행 필요.
			// 단 AI의 한정으로 하여 제한을 걸어줘야 한다.
			bOutOfHealth = false;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningAbilitySystemComponent()->GetAvatarActor(), MU_EVENT_REGENERATED, FGameplayEventData());
		}
	}

	if (Attribute == GetMaxHpAttribute())
	{
		SetCurrentHp(GetMaxHp());
	}
}

void UMUCharacterAttributeSetBase::HandleHPGameplayEffectCallback(const FGameplayEffectModCallbackData& Data)
{
	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* InstigatorActor = EffectContext.GetInstigator();
	
	const float MinHealth = 0.f;
	
	float TempDamage = GetDamage();
	
	SetCurrentHp(FMath::Clamp(GetCurrentHp() - GetDamage(),  MinHealth, GetMaxHp()));

	if ( TempDamage > 0.f && IsValid(InstigatorActor) == true )
	{
		//여기서 관련 데이터를 업데이팅을 해줘야 한다.
		FGameplayEventData EventData;
		EventData.Instigator = GetOwningAbilitySystemComponent()->GetAvatarActor();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InstigatorActor, MU_EVENT_HITCOMPLETE, EventData);
	}

	SetDamage(0);	
}

void UMUCharacterAttributeSetBase::CheckDeath(const FGameplayEffectModCallbackData& Data)
{
	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* InstigatorActor = EffectContext.GetInstigator();

	if ( IsValid( InstigatorActor ) == false )
	{
		return;
	}
	
	if (GetCurrentHp() <= 0.0f && !bOutOfHealth)
	{
		//죽었을 시 추가적인 처리가 필요하다.
		FGameplayEventData EventData;
		
		FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
		
		TArray<TWeakObjectPtr<AActor>> TargetActor;
		TargetActor.Add(InstigatorActor);
		TargetData->SetActors(TargetActor);
		
		EventData.TargetData.Add(TargetData);
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningAbilitySystemComponent()->GetAvatarActor(), MU_CHARACTERSTATE_DEAD, EventData);

		UE_LOG(LogTemp, Log, TEXT("Character Death"));
	}
	
	bOutOfHealth = (GetCurrentHp() <= 0.0f);
}

bool UMUCharacterAttributeSetBase::HandlePreDamage(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		FGameplayModifierEvaluatedData& EvaluatedData = Data.EvaluatedData;
		UAbilitySystemComponent& Target = Data.Target;
		if (EvaluatedData.Magnitude > 0.0f)
		{
			//Target.HasMatchingGameplayTag(MU_CHARACTERSTATE_DODGE) || Target.HasMatchingGameplayTag(MU_CHARACTERSTATE_PARRY) || Target.HasMatchingGameplayTag(MU_CHARACTERSTATE_SUPERARMOR)
			if (Target.HasAnyMatchingGameplayTags(IgnoranceDamageTags))
			{
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}

			if (Target.HasAnyMatchingGameplayTags(DefenseTags))
			{
				Data.EvaluatedData.Magnitude *= GetDefendRate();
				return true;
			}
		}
	}

	return true;
}
