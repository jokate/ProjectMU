// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_TimeWinding.h"

#include "AIController.h"
#include "Interface/TimerWindTarget.h"

bool UBTD_TimeWinding::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!Pawn)
	{
		return false;
	}

	ITimeWindTarget* Target = Cast<ITimeWindTarget>(Pawn);

	if (Target == nullptr)
	{
		return false;
	}
	
	return Target->GetTimeWind();
}
