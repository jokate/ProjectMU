// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_Dead.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_Dead : public UGameplayAbility
{
	GENERATED_BODY()
	
public : 

	UMUGA_Dead();

protected :
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void OnCharacterDead();
	
	UFUNCTION()
	void OnDeadAnimationEnded();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> DeadAnimMontage;
};

