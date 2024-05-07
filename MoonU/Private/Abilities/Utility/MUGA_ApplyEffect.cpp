// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_ApplyEffect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

UMUGA_ApplyEffect::UMUGA_ApplyEffect()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_ApplyEffect::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());
	const IAbilitySystemInterface* InstigatorASI = Cast<IAbilitySystemInterface>(TriggerEventData->Instigator);

	const UAbilitySystemComponent* InstigatorASC = InstigatorASI->GetAbilitySystemComponent();

	switch (EffectApplicationMode)
	{
	case Self :
		{
			FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffect);
			if (EffectSpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle);
			}
		}
	case Target :
		{
			FGameplayEffectContextHandle EffectContextHandle = InstigatorASC->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = InstigatorASC->MakeOutgoingSpec(GameplayEffect, TriggerEventData->EventMagnitude, EffectContextHandle);

			if (EffectSpecHandle.IsValid())
			{
				ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle);
			}
		}
	}
	

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
