// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AI/AIEnum.h"
#include "Navigation/PathFollowingComponent.h"
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

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void OnCompleteMove(const FAIRequestID RequestID, EPathFollowingResult::Type InType);

	void OnRetriggered(const FGameplayEventData* EventData);

	UPROPERTY(EditDefaultsOnly)
	FName TargetKeyName;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EBlackboardKeyData> BlackboardKeyData;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius;
	
	UPROPERTY()
	TObjectPtr<class UMUAT_MoveToAI> MoveToAITask;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag RetriggerTag;
};
