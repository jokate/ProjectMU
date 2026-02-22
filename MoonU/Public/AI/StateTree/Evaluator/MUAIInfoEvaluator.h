// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "UObject/Object.h"
#include "MUAIInfoEvaluator.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMUAIInfoInstanceData
{
	GENERATED_BODY()

public :
	UPROPERTY(VisibleAnywhere, Category = "Output")
	float AttackDistance = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Output")
	float DefendDistance = 0.f;

	// 차후 여기에 계속 전개.
};

USTRUCT()
struct MOONU_API FMUAIInfoEvaluator : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()

public :
	
	using FInstanceDataType = FMUAIInfoInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
};
