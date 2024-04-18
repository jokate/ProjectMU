﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_AttackTrace.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "ParticleHelper.h"
#include "Abilities/AT/MUAT_Trace.h"
#include "Perception/AISense_Damage.h"

UMUGA_AttackTrace::UMUGA_AttackTrace()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AttackTrace::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CurrentCombo = TriggerEventData->EventMagnitude;
	
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
		const TArray<TWeakObjectPtr<AActor>> TriggerActors = TargetDataHandle.Data[0].Get()->GetActors();

		AActor* CurrentActor = CurrentActorInfo->AvatarActor.Get();

		// Hit에 대한 인포 제공 + 데미지 적용 필요.
		for (const auto& TriggerActor : TriggerActors)
		{
			AActor* TriggeredActor = TriggerActor.Get();

			if (!TriggeredActor)
			{
				continue;
			}

			UAISense_Damage::ReportDamageEvent(CurrentActor, TriggeredActor, CurrentActor, 0.0f, TriggerActor->GetActorLocation(), TriggerActor->GetActorLocation());
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TriggeredActor, MU_EVENT_ONHIT, FGameplayEventData());
		}

		UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();

		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, CurrentCombo);

		if (EffectSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);
		}
	} 
	
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
