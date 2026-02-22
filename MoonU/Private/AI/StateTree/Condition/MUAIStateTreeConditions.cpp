// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Condition/MUAIStateTreeConditions.h"

bool FMUAIStateTreeCondition_IsAttackable::TestCondition(FStateTreeExecutionContext& Context) const
{
	return FStateTreeConditionCommonBase::TestCondition(Context);
}
