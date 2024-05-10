// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_TimeStopTarget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"


void UMUGA_TimeStopTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		TargetActor->CustomTimeDilation = TIMESTOPDILATION;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.FindOrAdd(MU_EVENT_TIMESTOPEND).AddUObject(this, &ThisClass::OnTimeStopEnd);
	}
}

void UMUGA_TimeStopTarget::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		TargetActor->CustomTimeDilation = ORIGINALTIME;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.Remove(MU_EVENT_TIMESTOPEND);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_TimeStopTarget::OnTimeStopEnd(const FGameplayEventData* EventData)
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
