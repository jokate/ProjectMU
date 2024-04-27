// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_SetTimerForChangeValue.h"

#include "AIController.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_SetTimerForChangeValue::UBTS_SetTimerForChangeValue()
{
	bNotifyBecomeRelevant = true;

	bNotifyCeaseRelevant = true;
}

void UBTS_SetTimerForChangeValue::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	OnTimerEnd.BindUObject(this, &UBTS_SetTimerForChangeValue::SetTimerForChangeValue, TWeakObjectPtr<UBehaviorTreeComponent>(&OwnerComp));
	GetWorld()->GetTimerManager().SetTimer(ChangeTimer, this, &UBTS_SetTimerForChangeValue::BroadcastEvent, TimerInterval);
}

void UBTS_SetTimerForChangeValue::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OnTimerEnd.Unbind();
	GetWorld()->GetTimerManager().ClearTimer(ChangeTimer);
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

void UBTS_SetTimerForChangeValue::SetTimerForChangeValue(TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp)
{
	UBehaviorTreeComponent* BehaviorTreeComponent = OwnerComp.Get();

	if (BehaviorTreeComponent == nullptr)
	{
		return;
	}

	AAIController* AIController = BehaviorTreeComponent->GetAIOwner();

	if (AIController == nullptr)
	{
		return;
	}

	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		return;
	}
	
	switch (DataTypeToChange)
	{
	case BoolType :
		BBComponent->SetValueAsBool(SelectedKey.SelectedKeyName, ChangeValBool);
		break;
	case FloatType:
		BBComponent->SetValueAsFloat(SelectedKey.SelectedKeyName, ChangeValFloat);
		break;
	case IntType:
		BBComponent->SetValueAsInt(SelectedKey.SelectedKeyName, ChangeValInt);
		break;
	case VectorType:
		BBComponent->SetValueAsVector(SelectedKey.SelectedKeyName, ChangeValVector);
		break;
	default :
		break;
	}
}

void UBTS_SetTimerForChangeValue::BroadcastEvent()
{
	if (OnTimerEnd.IsBound())
	{
		OnTimerEnd.Execute();
	}
}
