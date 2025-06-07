// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_ActivateSkill.h"
#include "MUGA_InstantSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_InstantSkill : public UMUGA_ActivateSkill
{
	GENERATED_BODY()

public :
	UMUGA_InstantSkill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void ActivateSkill() override;
};
