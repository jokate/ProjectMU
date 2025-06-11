// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_PlayMontage.h"
#include "MUGA_HitReaction.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_HitReaction : public UMUGA_PlayMontage
{
	GENERATED_BODY()

	UMUGA_HitReaction();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
public :
	
};
