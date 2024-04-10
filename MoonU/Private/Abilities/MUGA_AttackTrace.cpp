// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_AttackTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
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

	UMUAT_Trace* AttackTraceTask = UMUAT_Trace::CreateTask(this, TraceClass);

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
	if (UAbilitySystemBlueprintLibrary::TargetDataHasActor(TargetDataHandle, 0))
	{
		UE_LOG(LogTemp, Log, TEXT("Target Is Avaliable"));
	} 
	
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
