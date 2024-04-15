// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FocusTarget.h"

#include "AIController.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTFunctionLibrary.h"

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const auto* BBAsset = GetBlackboardAsset();

	if (BBAsset == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetBlackboardKey.SelectedKeyName));
	
	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AIController->SetFocus(TargetActor);

	return EBTNodeResult::Succeeded;
}
