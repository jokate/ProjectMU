﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Skill/MUGA_IndicatorSkill.h"
#include "MUGA_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_ChargeAttack : public UMUGA_IndicatorSkill
{
	GENERATED_BODY()

public :
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void ActivateSkill() override;
protected:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> MontageToPlay;
};
