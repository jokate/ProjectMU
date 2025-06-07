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

public :
	UMUGA_IndicatorSkill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void ActivateSkill() override;

	UFUNCTION()
	virtual void OnSkillInputPressed();

	UFUNCTION()
	virtual void OnSkillCanceled();
};
