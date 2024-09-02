// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_DropExperience.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_DropExperience : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_DropExperience();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DropEXP | Level")
	float Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DropEXP | EffectClass")
	TSubclassOf<UGameplayEffect> DropExpClass;
};
