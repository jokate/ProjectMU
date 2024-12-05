// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_TargetIsValid.h"

#include "AIController.h"
#include "Interface/MUEnemy.h"

bool UBTD_TargetIsValid::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if ( IsValid( OwnerPawn ) == false )
	{
		return false;
	}

	IMUEnemy* MUEnemy = Cast<IMUEnemy>(OwnerPawn);
	
	if ( MUEnemy == nullptr )
	{
		return false;
	}

	AActor* TargetActor = MUEnemy->GetActorTarget();
	return IsValid(TargetActor);
}
