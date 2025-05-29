// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_ActivateSkill.h"
#include "Data/MUStruct.h"

void UMUGA_ActivateSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ActivateSkill();
}