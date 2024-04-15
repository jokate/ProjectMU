// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUBTTaskNode.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTTask_Attack : public UMUBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void AttackFinished(const FGameplayEventData* EventData);

	void OnAttackFinished(UBehaviorTreeComponent& OwnerComp, const FGameplayEventData* EventData);
	
};
