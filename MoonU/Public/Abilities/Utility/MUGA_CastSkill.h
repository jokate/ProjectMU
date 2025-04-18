﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MUEnum.h"
#include "MUGA_CastSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_CastSkill : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_CastSkill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY( EditDefaultsOnly )
	ESkillSlotType CastSkillSlotType;
};
