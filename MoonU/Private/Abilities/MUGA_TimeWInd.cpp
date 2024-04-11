// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_TimeWInd.h"

#include "Interface/TimeWinder.h"

void UMUGA_TimeWInd::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	ITimeWinder* TimeWinder = GetWorld()->GetAuthGameMode<ITimeWinder>();

	if (TimeWinder)
	{
		TimeWinder->TimeWindActivate();
	}
}

void UMUGA_TimeWInd::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
		
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_TimeWInd::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ITimeWinder* TimeWinder = GetWorld()->GetAuthGameMode<ITimeWinder>();

	if (TimeWinder)
	{
		TimeWinder->TimeWindDeactivate();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
