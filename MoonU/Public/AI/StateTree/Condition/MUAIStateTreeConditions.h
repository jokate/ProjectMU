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
	UPROPERTY(EditAnywhere, Category = "Source")
	TObjectPtr<AActor> Source;

	UPROPERTY(EditAnywhere, Category = "Target")
	TObjectPtr<AActor> Target;
};
USTRUCT()
struct MOONU_API FMUAIStateTreeCondition_IsAttackableDistance : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

public :
	using FInstanceDataType = FStateTreeCompareTarget;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;

public :
	UPROPERTY(EditAnywhere, Category = "Error Margin")
	float ErrorMargin = 0.f;

	UPROPERTY(EditAnywhere, Category = "Data")
	float Distance = 0.f;
};
