// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_PlayTimeline.h"

#include "Interface/TimelinePlayer.h"

UMUGA_PlayTimeline::UMUGA_PlayTimeline()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_PlayTimeline::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	ITimelinePlayer* Player = Cast<ITimelinePlayer>(ActorInfo->AvatarActor.Get());

	if (Player)
	{
		Player->PlayTimeline();
	}
}

void UMUGA_PlayTimeline::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ITimelinePlayer* Player = Cast<ITimelinePlayer>(ActorInfo->AvatarActor.Get());

	if (Player)
	{
		Player->ReverseTimeline();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}