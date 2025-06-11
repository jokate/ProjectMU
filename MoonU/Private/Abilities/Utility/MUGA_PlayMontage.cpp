// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_PlayMontage.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Interface/MotionWarpTarget.h"


UMUGA_PlayMontage::UMUGA_PlayMontage()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bRetriggerInstancedAbility = true;
}

void UMUGA_PlayMontage::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayMontage"), MontageToPlay);

	PlayMontageTask->OnCompleted.AddDynamic(this, &UMUGA_PlayMontage::OnMontagePlayed);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UMUGA_PlayMontage::OnMontageInterrupted);
	PlayMontageTask->OnBlendOut.AddDynamic(this, &UMUGA_PlayMontage::OnMontageInterrupted);
	PlayMontageTask->OnCancelled.AddDynamic(this, &UMUGA_PlayMontage::OnMontageInterrupted);
	
	PlayMontageTask->ReadyForActivation();
}

void UMUGA_PlayMontage::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_PlayMontage::OnMontagePlayed()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_PlayMontage::OnMontageInterrupted()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

