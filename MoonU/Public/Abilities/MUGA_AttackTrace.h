// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MU_AbilityBase.h"
#include "MUGA_AttackTrace.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AttackTrace : public UMU_AbilityBase
{
	GENERATED_BODY()
	UMUGA_AttackTrace();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected :
	UFUNCTION()
	void OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMUTA_Trace> TraceClass;
};
