// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "BTTask_Patrol.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPatrolFinished);

UCLASS()
class MOONU_API UBTTask_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

protected :
	FOnPatrolFinished OnPatrolFinished;
};
