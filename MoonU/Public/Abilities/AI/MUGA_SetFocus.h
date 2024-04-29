// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_SetFocus : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_SetFocus();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void SetFocus();
	
	UPROPERTY(EditAnywhere)
	FName TargetActorKey;
	
	UPROPERTY(EditAnywhere)
	uint8 bSetFocus : 1;
};
