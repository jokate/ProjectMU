// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_ActivateSkill.h"
#include "MUGA_IndicatorSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_IndicatorSkill : public UMUGA_ActivateSkill
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void SkillTriggered(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	UFUNCTION()
	virtual void OnSkillInputPressed();

	UFUNCTION()
	virtual void OnSkillCanceled();
};
