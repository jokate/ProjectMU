// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_ChangeBlackboardValue.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_ChangeBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		return EBTNodeResult::Failed;
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
			UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName.ToString(), true);
			if (!Enum)
			{
				break;
			}

			BBComponent->SetValueAsEnum(SelectedKey.SelectedKeyName, Enum->GetValueByName(EnumValue));
		}
	default :
		break;
	}

	return EBTNodeResult::Succeeded;
}
