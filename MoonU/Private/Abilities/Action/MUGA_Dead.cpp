// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_Dead.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMUGA_Dead::UMUGA_Dead()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_Dead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* TargetCharacter = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

	if (TargetCharacter == nullptr)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	auto* CharacterMovement = TargetCharacter->GetCharacterMovement();

	if (CharacterMovement == nullptr)
	{
		return;
	}

	CharacterMovement->SetMovementMode(EMovementMode::MOVE_None);
	TargetCharacter->SetActorEnableCollision(false);

	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DEADMONTAAGE"), DeadAnimMontage);
	MontageTask->OnCompleted.AddDynamic(this, &UMUGA_Dead::OnDeadAnimationEnded);

	MontageTask->ReadyForActivation();
	
	
}

void UMUGA_Dead::OnDeadAnimationEnded()
{
}