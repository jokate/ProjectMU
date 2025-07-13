// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_PlayerAttack.h"

void UMUGA_PlayerAttack::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	ReserveAttack();
}
