// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_ActivateSkill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

UMUGA_ActivateSkill::UMUGA_ActivateSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_ActivateSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->ExecuteGameplayCue(GameplayCueTag);
		}
	}
}

void UMUGA_ActivateSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->InvokeGameplayCueEvent(GameplayCueTag, EGameplayCueEvent::Removed);
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_ActivateSkill::ActivateSkill()
{
	ApplyCost( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo );
	ApplyCooldown( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo );
}

void UMUGA_ActivateSkill::SkillTriggered(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// 여부에 따라서 스킬 트리거가 바로 Ability를 실행 할 수도 혹은 실행된 상태에서만 동작할 수도 있음.  ( 테스트 필요함 )
}

void UMUGA_ActivateSkill::SkillUnTriggered(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	CancelSkill();
	EndAbility( Handle, ActorInfo, ActivationInfo, true, true );
}