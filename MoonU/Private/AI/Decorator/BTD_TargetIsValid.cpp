// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_TargetIsValid.h"

#include "AIController.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/MUEnemy.h"

bool UBTD_TargetIsValid::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if ( IsValid( OwnerPawn ) == false )
	{
		return false;
	}
	
	AAIController* AIController = Cast<AAIController>(OwnerPawn->Controller);

	if ( IsValid(AIController) == false)
	{
		return false;
	}
	
	UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();

	if ( IsValid( BBComp ) == false )
	{
		return false;
	}

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(MU_AI_TARGET));
	
	return IsValid( TargetActor );
}
