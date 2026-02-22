// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Condition/MUAIStateTreeConditions.h"

#include "AIController.h"
#include "StateTreeExecutionContext.h"

bool FMUAIStateTreeCondition_IsAttackableDistance::TestCondition(FStateTreeExecutionContext& Context) const
{
	UObject* ContextObject = Context.GetOwner();
	if ( IsValid(ContextObject) == false )
	{
		return false;
	}

	AAIController* AIController = Cast<AAIController>(ContextObject);

	if (IsValid(AIController) == false)
	{
		return false;
	}

	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	AActor* TargetActor = InstanceData.Target;
	AActor* SourceActor = InstanceData.Source;
	if ( IsValid(TargetActor) == false || IsValid(SourceActor) == false )
	{
		return false;
	}

	const float ToDistance = TargetActor->GetDistanceTo(SourceActor);

	return ToDistance - ErrorMargin <= Distance;
}
