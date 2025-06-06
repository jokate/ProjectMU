// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

void UMUGA_IndicatorSkill::SkillTriggered(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::SkillTriggered(Handle, ActorInfo, ActivationInfo);

	ActivateSkill();
}
