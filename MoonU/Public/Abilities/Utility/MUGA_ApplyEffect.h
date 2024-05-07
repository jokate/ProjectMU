// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MUEnum.h"
#include "MUGA_ApplyEffect.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_ApplyEffect : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_ApplyEffect();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect To Apply")
	TEnumAsByte<EEffectApplicationMode> EffectApplicationMode;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect To Apply")
	TSubclassOf<class UGameplayEffect> GameplayEffect;
};
