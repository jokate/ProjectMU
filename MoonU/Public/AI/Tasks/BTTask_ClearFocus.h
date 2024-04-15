// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUBTTaskNode.h"
#include "BTTask_ClearFocus.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTTask_ClearFocus : public UMUBTTaskNode
{
	GENERATED_BODY()

public :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
