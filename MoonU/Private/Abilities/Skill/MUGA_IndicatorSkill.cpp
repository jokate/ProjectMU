// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

#include "Abilities/AT/MUAT_ShowIndicator.h"
#include "Data/MUStruct.h"

UMUGA_IndicatorSkill::UMUGA_IndicatorSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_IndicatorSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const FGameplayEventData_Skill* EventData = static_cast<const FGameplayEventData_Skill*>(TriggerEventData);

	if ( EventData == nullptr )
	{
		return;
	}

	UMUAT_ShowIndicator* ShowIndicatorTask = UMUAT_ShowIndicator::CreateTask( this, EventData->IndicatorMaterial, EventData->CastingRange);
	ShowIndicatorTask->ReadyForActivation();
}

void UMUGA_IndicatorSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ActivateSkill();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_IndicatorSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
