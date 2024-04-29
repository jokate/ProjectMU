// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_Regenerate.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_Regenerate : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_Regenerate();
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void RegenerateOperation();
};
