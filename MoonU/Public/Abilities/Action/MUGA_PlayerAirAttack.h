// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_PlayerAttack.h"
#include "MUGA_PlayerAirAttack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_PlayerAirAttack : public UMUGA_PlayerAttack
{
	GENERATED_BODY()

public :
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
