// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_ActivateSkill.h"
#include "MUGA_TimeStop.generated.h"

/**
 * 
 */
UCLASS() 
class MOONU_API UMUGA_TimeStop : public UMUGA_ActivateSkill
{
	GENERATED_BODY()

public :
	UMUGA_TimeStop();
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	void OnTimeFinished();

	virtual void ActivateSkill() override;

	virtual void SkillTriggered(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	FTimerHandle TimeStopHandle;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer GameplayCueTags;
};

