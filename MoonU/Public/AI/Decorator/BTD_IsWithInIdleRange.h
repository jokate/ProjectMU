// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsWithInIdleRange.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTD_IsWithInIdleRange : public UBTDecorator
{
	GENERATED_BODY()

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


public :
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector BlackboardKey;

	UPROPERTY(EditAnywhere, Category = ErrorMargin)
	float ErrorMargin;
};
