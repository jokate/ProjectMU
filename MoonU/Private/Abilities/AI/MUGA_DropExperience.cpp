// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_DropExperience.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

UMUGA_DropExperience::UMUGA_DropExperience()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_DropExperience::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
 	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* CurrentASC = GetAbilitySystemComponentFromActorInfo();

	if (IsValid(CurrentASC) == false)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	const FGameplayAbilityTargetDataHandle TargetData = TriggerEventData->TargetData;

	const FGameplayAbilityTargetData* AbilityTargetData = TargetData.Get(0);

	//Data Table에서 가져올 수 있도록 설계가 필요, 현재는 임시적인 처리로 진행한다.
	if (AbilityTargetData != nullptr)
	{
		TArray<TWeakObjectPtr<AActor>> TargetActors = AbilityTargetData->GetActors();
		FGameplayEffectContextHandle EffectContext = CurrentASC->MakeEffectContext();
		for (TWeakObjectPtr<AActor> TargetActor : TargetActors)
		{
			AActor* TargetActorGet = TargetActor.Get();

			if (IsValid(TargetActorGet) == true)
			{
				UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActorGet);

				if (IsValid(TargetASC) == false)
				{
					continue;
				}
				
				CurrentASC->BP_ApplyGameplayEffectToTarget(DropExpClass, TargetASC, Level, EffectContext);
			}
		}
	}

	// 경험치 처리가 종료 되었을 경우에는 Ability를 종료한다.
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
