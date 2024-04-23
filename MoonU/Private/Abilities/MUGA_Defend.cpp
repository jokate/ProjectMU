// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_Defend.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMUGA_Defend::UMUGA_Defend()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	Interval = 0.2f;
}

void UMUGA_Defend::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* CurrentActor = CurrentActorInfo->AvatarActor.Get();

	if (CurrentActor)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurrentActor);

		if (ASC)
		{
			ASC->AddLooseGameplayTag(MU_CHARACTERSTATE_PARRY);
		}
	}
	
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DEFENSEMONTAGE"), DefenseMontage);
	
	PlayMontageAndWait->ReadyForActivation();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMUGA_Defend::RemoveParryTag, Interval);
}

void UMUGA_Defend::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	RemoveParryTag();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_Defend::RemoveParryTag()
{
	AActor* CurrentActor = CurrentActorInfo->AvatarActor.Get();

	if (CurrentActor)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurrentActor);

		if (ASC)
		{
			if (ASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_PARRY))
			{
				ASC->RemoveLooseGameplayTag(MU_CHARACTERSTATE_PARRY);	
			}
		}
	}
}

void UMUGA_Defend::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
