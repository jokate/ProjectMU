﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_Dead.h"
#include "MUGA_PlayerDead.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_PlayerDead : public UMUGA_Dead
{
	GENERATED_BODY()

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
