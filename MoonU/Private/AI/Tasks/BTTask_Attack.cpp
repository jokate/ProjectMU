// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Attack.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BTFunctionLibrary.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);

	if (AbilitySystemComponent == nullptr) 
	{
		return EBTNodeResult::Failed;	
	}

	TaskFinished.AddLambda(
		[&] (const FGameplayEventData* EventData)
		{
			OnAttackFinished(OwnerComp, EventData);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
	
	AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(MU_EVENT_ATTACKFINISHED).AddUObject(this, &UBTTask_Attack::AttackFinished);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ControllingPawn, MU_EVENT_ATTACKSTARTED, FGameplayEventData());
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::AttackFinished(const FGameplayEventData* EventData)
{
	TaskFinished.Broadcast(EventData);
}

void UBTTask_Attack::OnAttackFinished(UBehaviorTreeComponent& OwnerComp, const FGameplayEventData* EventData)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerComp.GetAIOwner()->GetPawn());

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.Remove(MU_EVENT_ATTACKFINISHED);
	}
}
