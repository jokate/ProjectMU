// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_TraceForInteraction.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_TraceForInteraction : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UMUGA_TraceForInteraction();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void SetTargetActor(AActor* TargetActor);
protected :
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float InteractionRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess))
	float LineCastLength;
};
