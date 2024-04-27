// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_SetFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_SetFocus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr)
	{
		return;
	}
	
	if (bSetFocus)
	{
		UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

		if (BBComponent)
		{
			AActor* TargetActor = Cast<AActor>(BBComponent->GetValueAsObject(TargetActorKey.SelectedKeyName));

			if (TargetActor)
			{
				AIController->SetFocus(TargetActor);
			}
		}
	}
	else
	{
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
	}
}
