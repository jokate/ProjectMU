// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_IsWithInIdleRange.h"

#include "AIController.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_IsWithInIdleRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr)
	{
		return false; 
	}

	const UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (BlackboardComponent == nullptr)
	{
		return false;
	}

	UObject* Object = BlackboardComponent->GetValueAsObject(MU_AI_TARGET);

	if (Object == nullptr)
	{
		return false;
	}

	const AActor* TargetActor = Cast<AActor>(Object);

	if (TargetActor == nullptr)
	{
		return false;
	}

	const float DistanceToTarget = TargetActor->GetDistanceTo(AIController->GetPawn());

	const float SelectedKeyValue = BlackboardComponent->GetValueAsFloat(BlackboardKey.SelectedKeyName);

	return DistanceToTarget - ErrorMargin <= SelectedKeyValue;
} 
