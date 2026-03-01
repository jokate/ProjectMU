// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_AttackTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/AT/MUAT_Trace.h"

UMUGA_AttackTrace::UMUGA_AttackTrace()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AttackTrace::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_Trace* AttackTraceTask = UMUAT_Trace::CreateTask(this, TraceName);

	AttackTraceTask->OnComplete.AddDynamic(this, &UMUGA_AttackTrace::OnTraceResultCallback);
	AttackTraceTask->ReadyForActivation();
}

void UMUGA_AttackTrace::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_AttackTrace::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
