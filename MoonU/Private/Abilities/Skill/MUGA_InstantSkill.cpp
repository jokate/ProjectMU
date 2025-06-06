// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_InstantSkill.h"

void UMUGA_InstantSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 스킬 활성화.
	ActivateSkill();
}

void UMUGA_InstantSkill::ActivateSkill()
{
	Super::ActivateSkill();
}
