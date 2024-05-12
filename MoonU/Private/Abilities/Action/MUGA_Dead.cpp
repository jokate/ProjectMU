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

	OnCharacterDead();
	
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DEADMONTAAGE"), DeadAnimMontage);
	MontageTask->ReadyForActivation();
}

void UMUGA_Dead::OnCharacterDead()
{
	ACharacter* TargetCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());

	if (TargetCharacter == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
	
	TargetCharacter->SetActorEnableCollision(false);
	
	auto* CharacterMovement = TargetCharacter->GetCharacterMovement();

	if (CharacterMovement == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	CharacterMovement->SetMovementMode(EMovementMode::MOVE_None);
}

void UMUGA_Dead::OnDeadAnimationEnded()
{
}
