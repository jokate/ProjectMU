// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_OrderTimeWind.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
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
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSet::GetCurrentTimeGaugeAttribute()).AddUObject(this, &UMUGA_OrderTimeWind::OnTimewindGaugeChanged);
	}

	EffectSpecHandle = MakeOutgoingGameplayEffectSpec(TimewindCost);

	if (EffectSpecHandle.IsValid())
	{
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectSpecHandle);
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

	if (TimeWinder)
	{
		TimeWinder->TimeWindDeactivate();
	}

	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(ActorInfo->AvatarActor.Get());

	if (TimeWindTarget)
	{
		TimeWindTarget->GetTimeWindEndEvent().RemoveAll(this);
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());
	
	if (ASC)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UMUCharacterAttributeSet::GetCurrentTimeGaugeAttribute()).RemoveAll(this);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
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
