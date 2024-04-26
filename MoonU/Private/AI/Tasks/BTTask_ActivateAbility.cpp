// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_ActivateAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ControllingPawn, StartAbilityTag, FGameplayEventData());
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_ActivateAbility::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

