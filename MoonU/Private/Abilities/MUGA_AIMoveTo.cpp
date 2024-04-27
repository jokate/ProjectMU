// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_AIMoveTo.h"

#include "Abilities/AT/MUAT_MoveToAI.h"

UMUGA_AIMoveTo::UMUGA_AIMoveTo()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AIMoveTo::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_MoveToAI* MoveTask = UMUAT_MoveToAI::CreateTask(this, TargetKeyName, BlackboardKeyData, AcceptanceRadius);

	MoveTask->MoveCompleted.AddDynamic(this, &UMUGA_AIMoveTo::OnCompleteMove);

	MoveTask->ReadyForActivation();
}

void UMUGA_AIMoveTo::OnCompleteMove()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
