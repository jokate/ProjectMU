// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "UObject/Object.h"
#include "MUAIPerceptionEvaluator.generated.h"

/**
 * 
 */

class UEnvQuery;

USTRUCT()
struct FMUAITargetInstancedData
{
	GENERATED_BODY()

public :
	void Reset()
	{
		TargetActor = nullptr;
	}
	
	UPROPERTY(VisibleAnywhere, Category = "Output")
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere, Category = "TargetEQS")
	TObjectPtr<UEnvQuery> TargetingEQS;
};


USTRUCT(meta = (DisplayName = "퍼셉션 모니터"))
struct MOONU_API FMUAIPerceptionEvaluator : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
public :
	using FInstanceDataType = FMUAITargetInstancedData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
};
