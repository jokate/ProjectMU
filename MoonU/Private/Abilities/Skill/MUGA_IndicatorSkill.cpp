// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

#include "Abilities/AT/MUAT_ShowIndicator.h"
#include "Data/MUStruct.h"

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

	UMUAT_ShowIndicator* ShowIndicatorTask = UMUAT_ShowIndicator::CreateTask( this, EventData->SkillIndicatorType, EventData->CastingRange);
	ShowIndicatorTask->ReadyForActivation();
}

void UMUGA_IndicatorSkill::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	ActivateSkill();
}
