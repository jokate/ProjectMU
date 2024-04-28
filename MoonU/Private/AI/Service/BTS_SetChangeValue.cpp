// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_SetChangeValue.h"

#include "AIController.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_SetChangeValue::UBTS_SetChangeValue()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = false;
	bNotifyCeaseRelevant = true;
}

void UBTS_SetChangeValue::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (bBecomeOrCeased)
	{
		ChangeValue(OwnerComp);
	}
}

void UBTS_SetChangeValue::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (bBecomeOrCeased == false)
	{
		ChangeValue(OwnerComp);
	}
	
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

void UBTS_SetChangeValue::ChangeValue(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

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
	case EnumType:
		{
			const UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName.ToString(), true);
			if (!Enum)
			{
				break;
			}

			BBComponent->SetValueAsEnum(SelectedKey.SelectedKeyName, Enum->GetValueByName(EnumValue));
		}
	default :
		break;
	}
}
