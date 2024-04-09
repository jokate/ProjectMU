// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_ChargeAttack : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_ChargeAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> MontageToPlay;
};
