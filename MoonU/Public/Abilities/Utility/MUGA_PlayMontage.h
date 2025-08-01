﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/MUEnum.h"
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

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void OnMontagePlayed();

	UFUNCTION()
	void OnMontageInterrupted();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> MontageToPlay;

	UPROPERTY(EditDefaultsOnly)
	bool bUseMotionWarp = false;

	UPROPERTY(EditDefaultsOnly)
	FName MotionWarpName = NAME_None;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EMotionWarpType> MotionWarpType = EMotionWarpType::NoneMotionWarp;
};
