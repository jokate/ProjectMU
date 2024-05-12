// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Action/MUGA_Dead.h"
#include "MUGA_AIDead.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AIDead : public UMUGA_Dead
{
	GENERATED_BODY()
	
protected :
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnGoldenTimeFinished();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float GoldenTimeInterval;
};
