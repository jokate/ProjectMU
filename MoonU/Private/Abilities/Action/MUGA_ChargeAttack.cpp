// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_ChargeAttack.h"

#include "MUDefines.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Character/MUCharacterPlayer.h"
#include "Library/MUFunctionLibrary.h"

void UMUGA_ChargeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMUGA_ChargeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(ActorInfo->OwnerActor.Get());
	
	if (MotionWarp != nullptr)
	{
		MotionWarp->ReleaseMotionWarp(DASH_MOTION_WARP);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_ChargeAttack::ActivateSkill()
{
	Super::ActivateSkill();

	AActor* OwnerActor = GetOwningActorFromActorInfo();
	
	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(OwnerActor);
	
	if (MotionWarp == nullptr)
	{
		return;
	}

	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Charge"), MontageToPlay,
		1.0f, NAME_None, true );
	NewTask->OnCompleted.AddDynamic(this, &UMUGA_ChargeAttack::OnCompleteCallback);
	NewTask->OnInterrupted.AddDynamic(this, &UMUGA_ChargeAttack::OnInterruptedCallback);
	NewTask->OnCancelled.AddDynamic(this, &UMUGA_ChargeAttack::OnInterruptedCallback);
	NewTask->OnBlendOut.AddDynamic(this, &UMUGA_ChargeAttack::OnInterruptedCallback);
	
	MotionWarp->SetMotionWarpToCursorDirection(DASH_MOTION_WARP, EMotionWarpType::TranslationAndRotation, TargetLocation, TargetRotation );
	
	NewTask->ReadyForActivation();
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
