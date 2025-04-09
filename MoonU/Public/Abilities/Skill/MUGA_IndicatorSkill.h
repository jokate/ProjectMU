// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/SkillActivateAbility.h"
#include "MUGA_IndicatorSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_IndicatorSkill : public UGameplayAbility, public ISkillActivateAbility
{
	GENERATED_BODY()

public :
	UMUGA_IndicatorSkill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void ActivateSkill() override {}

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
};
