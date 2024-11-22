// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_OrderTimeWind.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Attribute/MUTimewinderAttribute.h"
#include "Interface/TimerWindTarget.h"
#include "Interface/TimeWinder.h"

class ITimeWinder;

UMUGA_OrderTimeWind::UMUGA_OrderTimeWind()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_OrderTimeWind::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ITimeWinder* TimeWinder = GetWorld()->GetAuthGameMode<ITimeWinder>();

	if (TimeWinder)
	{
		TimeWinder->TimeWindActivate();
	}

	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(ActorInfo->AvatarActor.Get());

	if (TimeWindTarget)
	{
		TimeWindTarget->GetTimeWindEndEvent().AddUObject(this, &UMUGA_OrderTimeWind::OnTimewindEnded);
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUTimewinderAttribute::GetCurrentTimeGaugeAttribute()).AddUObject(this, &UMUGA_OrderTimeWind::OnTimewindGaugeChanged);
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->ExecuteGameplayCue(GameplayCueTag);	
		}
	}

	FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(TimewindCost);

	if (EffectSpecHandle.IsValid())
	{
		ActiveEffectSpecHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectSpecHandle);
	}
	
}

void UMUGA_OrderTimeWind::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_OrderTimeWind::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ITimeWinder* TimeWinder = GetWorld()->GetAuthGameMode<ITimeWinder>();

	if (TimeWinder != nullptr)
	{
		TimeWinder->TimeWindDeactivate();
	}

	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(ActorInfo->AvatarActor.Get());

	if (TimeWindTarget)
	{
		TimeWindTarget->GetTimeWindEndEvent().RemoveAll(this);
	}

	if (ActiveEffectSpecHandle.IsValid())
	{
		BP_RemoveGameplayEffectFromOwnerWithHandle(ActiveEffectSpecHandle);
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());
	
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUTimewinderAttribute::GetCurrentTimeGaugeAttribute()).RemoveAll(this);

		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->InvokeGameplayCueEvent(GameplayCueTag, EGameplayCueEvent::Removed);	
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UMUGA_OrderTimeWind::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());
	
	if (ASC == nullptr)
	{
		return false;
	}

	const auto* AttributeSet = ASC->GetSet<UMUTimewinderAttribute>();

	if (AttributeSet == nullptr)
	{
		return false;
	}

	float TimeGauge = AttributeSet->GetCurrentTimeGauge();

	bResult &= TimeGauge > 0.0f;

	return bResult;
}

void UMUGA_OrderTimeWind::OnTimewindGaugeChanged(const FOnAttributeChangeData& ChangedData)
{
	if (ChangedData.NewValue <= 0.0f)
	{
		bool bReplicatedEndAbility = true;
		bool bWasCancelled = false;
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
	}
}

void UMUGA_OrderTimeWind::OnTimewindEnded()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
