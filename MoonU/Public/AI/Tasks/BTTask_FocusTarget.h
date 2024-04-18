// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FocusTarget.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTTask_FocusTarget : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public :
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetBlackboardKey;
};
