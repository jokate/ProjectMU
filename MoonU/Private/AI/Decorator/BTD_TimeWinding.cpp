// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_TimeWinding.h"

#include "AIController.h"
#include "Interface/TimerWindTarget.h"

UBTD_TimeWinding::UBTD_TimeWinding()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

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

void UBTD_TimeWinding::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwnerPawn == nullptr)
	{
		return;
	}

	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(OwnerPawn);

	if (TimeWindTarget == nullptr)
	{
		return;
	}

	TimeWindTarget->GetTimeWindStateChangeEvent().AddUObject(this, &UBTD_TimeWinding::OnTimeWindStateChanged, TWeakObjectPtr<UBehaviorTreeComponent>(&OwnerComp), NodeMemory);
}

void UBTD_TimeWinding::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwnerPawn == nullptr)
	{
		return;
	}

	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(OwnerPawn);

	if (TimeWindTarget == nullptr)
	{
		return;
	}

	TimeWindTarget->GetTimeWindStateChangeEvent().RemoveAll(this);
}

void UBTD_TimeWinding::OnTimeWindStateChanged(bool bIsActive, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp,
                                              uint8* NodeMemory)
{
	if (!OwnerComp.IsValid())
	{
		return;
	}

	ConditionalFlowAbort(*OwnerComp, EBTDecoratorAbortRequest::ConditionResultChanged);
}
