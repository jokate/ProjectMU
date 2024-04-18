// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Patrol.h"

#include "AIController.h"
#include "Interface/Patroller.h"

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result =  Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwnerPawn == nullptr)
	{
		return EBTNodeResult::Failed;	
	}

	IPatroller* Patroller = Cast<IPatroller>(OwnerPawn);

	if (Patroller == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	const FVector PatrolRoute = Patroller->GetPositionForSpline();

	AAIController* OwnerController = OwnerComp.GetAIOwner();

	if (OwnerController)
	{	
		OwnerController->MoveToLocation(PatrolRoute, 10, false);
		Patroller->IncrementPatrolRoute();
		
		OnPatrolFinished.AddLambda([&]()
		{	
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		} );
		
		OwnerController->ReceiveMoveCompleted.AddUniqueDynamic(this, &UBTTask_Patrol::OnMoveCompleted);
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	OnPatrolFinished.Broadcast();
}
