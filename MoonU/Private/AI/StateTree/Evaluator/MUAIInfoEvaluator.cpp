// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Evaluator/MUAIInfoEvaluator.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "StateTreeExecutionContext.h"
#include "Attribute/MUCharacterAttributeSetBase.h"

void FMUAIInfoEvaluator::TreeStart(FStateTreeExecutionContext& Context) const
{
	UObject* ContextObject = Context.GetOwner();
	if ( IsValid(ContextObject) == false )
	{
		return;
	}

	AAIController* AIController = Cast<AAIController>(ContextObject);

	if (IsValid(AIController) == false)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AIController->GetPawn());

	if (ASC == nullptr)
	{
		return;

	}

	const UMUCharacterAttributeSetBase* AttributeSet = ASC->GetSet<UMUCharacterAttributeSetBase>();

	if (IsValid(AttributeSet) == false)
	{
		return;
	}
	
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	InstanceData.AttackDistance = AttributeSet->GetAttackRange();
	InstanceData.DefendDistance = AttributeSet->GetDefendRange();
}
