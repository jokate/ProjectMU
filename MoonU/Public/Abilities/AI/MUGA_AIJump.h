// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_AIJump.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AIJump : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_AIJump();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnLaunchEnded();
};

