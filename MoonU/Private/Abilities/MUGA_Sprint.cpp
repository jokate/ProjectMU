// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_Sprint.h"

#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMUGA_Sprint::UMUGA_Sprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

void UMUGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	if (Character == nullptr)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();

	if (MovementComponent == nullptr)
	{
		return;
	}

	MovementComponent->MaxWalkSpeed = SPRINT_SPEED;
}


void UMUGA_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UMUGA_Sprint::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	if (Character == nullptr)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();

	if (MovementComponent == nullptr)
	{
		return;
	}

	MovementComponent->MaxWalkSpeed = WALK_SPEED;
}


