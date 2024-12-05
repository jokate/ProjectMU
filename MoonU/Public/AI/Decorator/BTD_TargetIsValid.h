// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_TargetIsValid.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTD_TargetIsValid : public UBTDecorator
{
	GENERATED_BODY()

public :
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
