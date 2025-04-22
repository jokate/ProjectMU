// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_InputTrigger.h"

#include "AbilitySystemComponent.h"

UMUGA_InputTrigger::UMUGA_InputTrigger()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_InputTrigger::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}
