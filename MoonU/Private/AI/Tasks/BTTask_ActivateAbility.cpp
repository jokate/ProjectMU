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

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);

	if (AbilitySystemComponent == nullptr) 
	{
		return EBTNodeResult::Failed;	
	}

	TaskFinishedGAS.AddLambda(
		[&] (const FGameplayEventData* EventData)
		{
			OnGASAbilityFinished(OwnerComp, EventData);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
	
	AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(EndAbilityTag).AddUObject(this, &UBTTask_ActivateAbility::GASAbilityFinished);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ControllingPawn, StartAbilityTag, FGameplayEventData());
	
	return EBTNodeResult::InProgress;
}

void UBTTask_ActivateAbility::GASAbilityFinished(const FGameplayEventData* EventData)
{
	TaskFinishedGAS.Broadcast(EventData);
}

void UBTTask_ActivateAbility::OnGASAbilityFinished(UBehaviorTreeComponent& OwnerComp, const FGameplayEventData* EventData)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerComp.GetAIOwner()->GetPawn());

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.Remove(EndAbilityTag);
	}
}
