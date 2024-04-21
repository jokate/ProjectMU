// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MUEnum.h"
#include "Perception/AIPerceptionTypes.h"
#include "MUGA_AIStateChanger.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AIStateChanger : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_AIStateChanger();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	void OnPerceptionChanged(const FGameplayEventData* EventData);
public :
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EndTriggerTag;
};
