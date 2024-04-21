// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_IsWithInIdleRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTD_IsWithInIdleRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
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

	UObject* Object = BlackboardComponent->GetValueAsObject(ActorKey.SelectedKeyName);

	if (Object == nullptr)
	{
		return false;
	}

	const AActor* InActor = Cast<AActor>(Object);

	if (InActor == nullptr)
	{
		return false;
	}

	const float DistanceToTarget = InActor->GetDistanceTo(AIController->GetPawn());

	const float SelectedKeyValue = BlackboardComponent->GetValueAsFloat(KeySelector.SelectedKeyName);

	return DistanceToTarget - ErrorMargin <= SelectedKeyValue;
}
