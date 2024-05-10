// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_TimeStop.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Attribute/MUCharacterAttributeSet.h"

UMUGA_TimeStop::UMUGA_TimeStop()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_TimeStop::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	if (ASC)
	{
		const UMUCharacterAttributeSet* CharacterAttribute = ASC->GetSet<UMUCharacterAttributeSet>();

		if (CharacterAttribute)
		{
			GetWorld()->GetTimerManager().SetTimer(TimeStopHandle, this, &UMUGA_TimeStop::OnTimeFinished, CharacterAttribute->GetTimeStopDuration(), false);
		}
	}
}

void UMUGA_TimeStop::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_TimeStop::OnTimeFinished()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
