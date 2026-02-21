// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/MUGameplayAbility.h"
#include "Data/MUEnum.h"
#include "MUGA_Rollout.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_Rollout : public UMUGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_Rollout();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void OnCompleteCallback();

	UFUNCTION()
	void OnInterruptedCallback();

	const FName GetCurrentMontageSection(float RecentedInput);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> AnimMontageForRollOut;
		
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EVelocityDirection>, FName> MontageSectionMap;

	float MinStaminaToUse = 3.0f;
};
