// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_OnHit.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UMUGA_OnHit::UMUGA_OnHit()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_OnHit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//꾸준하게 돌아가는 Ability -- 기능상 HitChecker의 기능.
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//해당 Ability는 Hit 정보 및 현재 플레이어의 방어 및 패리에 관한 정보를 기반으로 동작을 확립한다.
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
	
	ASC->GenericGameplayEventCallbacks.FindOrAdd(TriggerGameplayTag).AddUObject(this, &UMUGA_OnHit::OnHitCheckedCallback);
}

void UMUGA_OnHit::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	//해당 Ability는 Hit 정보 및 현재 플레이어의 방어 및 패리에 관한 정보를 기반으로 동작을 확립한다.
	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (ASC)
		{
			ASC->GenericGameplayEventCallbacks.Remove(TriggerGameplayTag);
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_OnHit::OnHitCheckedCallback(const FGameplayEventData* EventData)
{
	//hit에 따른 정보를 기반으로 타 어빌리티를 호출할 수 있도록 한다..

	const FGameplayAbilityTargetData* TargetData = EventData->TargetData.Get(0);

	if (TargetData == nullptr)
	{
		return;
	}

	const FHitResult* HitResult = TargetData->GetHitResult();

	if (HitResult == nullptr)
	{
		return;
	}
	
	// Hit에 관한 부분을 수행한다.
	for (const FGameplayTag& HitTag : GameplayTagContainer)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CurrentActorInfo->AvatarActor.Get(), HitTag, *EventData);
	}
}
