﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_ChargeAttack.h"

#include "MUDefines.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Character/MUCharacterPlayer.h"

UMUGA_ChargeAttack::UMUGA_ChargeAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_ChargeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	AMUCharacterBase* MUCharacter = Cast<AMUCharacterBase>(ActorInfo->AvatarActor.Get());
	
	if (!MUCharacter)
	{
		return;
	}

	UAbilitySystemComponent* ASC = MUCharacter->GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}

	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Charge"), MontageToPlay, 1.0f);
	NewTask->OnCompleted.AddDynamic(this, &UMUGA_ChargeAttack::OnCompleteCallback);
	NewTask->OnInterrupted.AddDynamic(this, &UMUGA_ChargeAttack::OnInterruptedCallback);
	NewTask->OnCancelled.AddDynamic(this, &UMUGA_ChargeAttack::OnInterruptedCallback);
	NewTask->OnBlendOut.AddDynamic(this, &UMUGA_ChargeAttack::OnInterruptedCallback);
	
	MUCharacter->SetMotionWarp(DASH_MOTION_WARP, EMotionWarpType::TranslationAndRotation, 500.0f);
	
	NewTask->ReadyForActivation();
}

void UMUGA_ChargeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AMUCharacterBase* MUCharacter = Cast<AMUCharacterBase>(ActorInfo->AvatarActor.Get());
	
	if (!MUCharacter)
	{
		return;
	}

	UAbilitySystemComponent* ASC = MUCharacter->GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UMUGA_ChargeAttack::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_ChargeAttack::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
