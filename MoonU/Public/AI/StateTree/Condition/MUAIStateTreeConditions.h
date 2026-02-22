// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"
#include "MUAIStateTreeConditions.generated.h"

/**
 * 
 */
USTRUCT()
struct FStateTreeCompareTarget
{
	GENERATED_BODY()

public :
	//UPROPERTY(EditAnywhere, Category = "")
};
USTRUCT()
struct MOONU_API FMUAIStateTreeCondition_IsAttackable : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

public :
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};
