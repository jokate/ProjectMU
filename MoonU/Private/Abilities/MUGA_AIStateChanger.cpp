// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_AIStateChanger.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "AI/MUAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"

UMUGA_AIStateChanger::UMUGA_AIStateChanger()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AIStateChanger::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	//해당 어빌리티에 대한 목적은, BT 상에서 State를 열어주는 데에 Focus를 둔다.
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor == nullptr)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (ASC == nullptr)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	//끝날 경우 Callback에 대한 수행작업.
	ASC->GenericGameplayEventCallbacks.FindOrAdd(EndTriggerTag).AddUObject(this, &UMUGA_AIStateChanger::OnPerceptionChanged);
}

void UMUGA_AIStateChanger::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (ASC)
		{
			ASC->GenericGameplayEventCallbacks.Remove(EndTriggerTag);
		}	
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_AIStateChanger::OnPerceptionChanged(const FGameplayEventData* EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
