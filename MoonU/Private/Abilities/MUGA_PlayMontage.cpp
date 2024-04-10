// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_PlayMontage.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"


UMUGA_PlayMontage::UMUGA_PlayMontage()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_PlayMontage::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("OnHit"), MontageToPlay, 1.0f);
	NewTask->OnCompleted.AddDynamic(this, &UMUGA_PlayMontage::OnCompleteCallback);
	NewTask->OnInterrupted.AddDynamic(this, &UMUGA_PlayMontage::OnInterruptedCallback);
	NewTask->OnCancelled.AddDynamic(this, &UMUGA_PlayMontage::OnInterruptedCallback);
	NewTask->OnBlendOut.AddDynamic(this, &UMUGA_PlayMontage::OnInterruptedCallback);

	NewTask->ReadyForActivation();
}

void UMUGA_PlayMontage::OnCompleteCallback()
{
	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_PlayMontage::OnInterruptedCallback()
{
	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
