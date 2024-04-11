﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MU_AbilityBase.h"
#include "MUGA_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_PlayMontage : public UMU_AbilityBase
{
	GENERATED_BODY()

public :
	UMUGA_PlayMontage();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> MontageToPlay;
};
