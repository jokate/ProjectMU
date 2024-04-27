// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_CancelAbilityByTag.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_CancelAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = AIController->GetPawn();

	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);

	if (ASC == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ASC->CancelAbilities(&NeedToCancelAbilityTags, nullptr);

	return EBTNodeResult::Succeeded;
}
