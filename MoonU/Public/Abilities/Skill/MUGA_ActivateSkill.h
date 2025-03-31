﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_ActivateSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_ActivateSkill : public UGameplayAbility
{
	GENERATED_BODY()

public :
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void ActivateInstantSkill() {};

	virtual void ActivateIndicatorSkill() {};
};
