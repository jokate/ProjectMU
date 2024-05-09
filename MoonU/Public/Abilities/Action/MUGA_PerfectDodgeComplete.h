// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_PerfectDodgeComplete.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_PerfectDodgeComplete : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_PerfectDodgeComplete();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void TimerEnded();
	
	FTimerHandle TimerHandle;

protected :
	UPROPERTY(EditDefaultsOnly)
	float TimerInterval;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> EffectForDodge;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = GameplayCue))
	FGameplayTagContainer GameplayCueTags;

	UPROPERTY(EditDefaultsOnly)
	float SlomoRate; 
};
