// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AI/AIEnum.h"
#include "MUGA_AIMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AIMoveTo : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_AIMoveTo();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnCompleteMove();

	UPROPERTY(EditDefaultsOnly)
	FName TargetKeyName;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EBlackboardKeyData> BlackboardKeyData;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius;
	
};
