// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_TimeWinding.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTD_TimeWinding : public UBTDecorator
{
	GENERATED_BODY()

	UBTD_TimeWinding();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnTimeWindStateChanged(bool bIsActive, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory);
};
