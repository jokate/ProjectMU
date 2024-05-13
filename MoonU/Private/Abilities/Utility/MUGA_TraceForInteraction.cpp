// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_TraceForInteraction.h"

#include "Abilities/AT/MUAT_TraceforInteraction.h"

UMUGA_TraceForInteraction::UMUGA_TraceForInteraction()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_TraceForInteraction::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_TraceforInteraction* NewTask = UMUAT_TraceforInteraction::CreateTask(this, InteractionRadius, LineCastLength);

	NewTask->
}

