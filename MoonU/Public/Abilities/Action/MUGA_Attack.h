﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_Attack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_Attack : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_Attack();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
protected:
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

	void ReserveAttack();

	FName GetNextSection();

	void StartComboTimer();

	void CheckComboInput();

	void UpdateComboTimer();
	
protected:
	UPROPERTY( EditDefaultsOnly )
	TObjectPtr<class UMUComboActionData> ComboData;

	uint8 CurrentCombo = 0;

	FTimerHandle ComboTimerHandle;

	bool HasNextComboInput = false;

	float MinStaminaToAttack;
};
