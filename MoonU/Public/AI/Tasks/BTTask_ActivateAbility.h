// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ActivateAbility.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskFinishedGAS, const FGameplayEventData* EventData);

UCLASS()
class MOONU_API UBTTask_ActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual void GASAbilityFinished(const FGameplayEventData* EventData);
	
	virtual void OnGASAbilityFinished(UBehaviorTreeComponent& OwnerComp, const FGameplayEventData* EventData);
protected :
	
	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag StartAbilityTag;

	UPROPERTY(EditAnywhere, Meta = (Categories = Event))
	FGameplayTag EndAbilityTag;
	
	FOnTaskFinishedGAS TaskFinishedGAS;
};
