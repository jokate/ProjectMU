// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_PerfectDodgeComplete.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"

UMUGA_PerfectDodgeComplete::UMUGA_PerfectDodgeComplete()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	SlomoRate = 0.75f;
}

void UMUGA_PerfectDodgeComplete::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
	{
		ASC->ExecuteGameplayCue(GameplayCueTag);	
	}

	AWorldSettings* WorldSettings = GetWorld()->GetWorldSettings();

	if (WorldSettings)
	{
		WorldSettings->SetTimeDilation(SlomoRate);
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMUGA_PerfectDodgeComplete::TimerEnded, TimerInterval, false);
}

void UMUGA_PerfectDodgeComplete::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	AWorldSettings* WorldSettings = GetWorld()->GetWorldSettings();

	if (WorldSettings)
	{
		WorldSettings->SetTimeDilation(1.0f);
	}
	
	if (IsValid(ASC) == true)
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->InvokeGameplayCueEvent(GameplayCueTag, EGameplayCueEvent::Removed);	
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_PerfectDodgeComplete::TimerEnded()
{
	bool bReplicatedEndAbility = true;
	bool bCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bCancelled);
}
