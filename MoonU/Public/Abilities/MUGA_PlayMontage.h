// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_PlayMontage : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_PlayMontage();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> MontageToPlay;
};
