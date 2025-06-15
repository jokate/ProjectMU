// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_InstantSkill.h"

#include "MUDefines.h"

UMUGA_InstantSkill::UMUGA_InstantSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityTags.AddTag(MU_SKILL_INSTANT);
	CancelAbilitiesWithTag.AddTag(MU_SKILL_INDICATOR);
	ActivationOwnedTags.AddTag(MU_SKILL_INSTANT);
}

void UMUGA_InstantSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 스킬 활성화.
	CastSkill();
}

void UMUGA_InstantSkill::ActivateSkill()
{
	Super::ActivateSkill();
}
