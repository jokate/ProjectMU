// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_Defend.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_Defend : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_Defend();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void RemoveParryTag();
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> DefenseMontage;

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float Interval;
};
