// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_OnHit.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_OnHit : public UGameplayAbility
{
	GENERATED_BODY()

	UMUGA_OnHit();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void OnHitCheckedCallback(const FGameplayEventData* EventData);

	bool CheckHitLocationIsInDefendBound(const FTransform& InTransform, const FVector& HitLocation, const FVector& Extent);

	bool CheckHitInstigatorActorInProperAngle(const AActor* CurrentActor, const AActor* InstigatorActor);
public :
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag TriggerGameplayTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer DefendStateTag;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer UnDefendStateTag;

	UPROPERTY(EditDefaultsOnly)
	float AngleMargin;
};
