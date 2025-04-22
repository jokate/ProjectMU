// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_InputTrigger.generated.h"

/**
 * 
 */

UCLASS()
class MOONU_API UMUGA_InputTrigger : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_InputTrigger();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public :
	UPROPERTY( EditDefaultsOnly )
	FGameplayTag InputTriggerTag;
};
