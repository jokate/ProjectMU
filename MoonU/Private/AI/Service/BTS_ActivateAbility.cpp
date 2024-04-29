// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_ActivateAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "GameplayTasksComponent.h"

UBTS_ActivateAbility::UBTS_ActivateAbility()
{
	bTickIntervals = true;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTS_ActivateAbility::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ServiceMode == EBTServiceActivationMode::TickNode)
	{
		ActivateAbility(OwnerComp);
	}
}

void UBTS_ActivateAbility::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ServiceMode == EBTServiceActivationMode::CeaseRelevant)
	{
		ActivateAbility(OwnerComp);	
	}
	
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

void UBTS_ActivateAbility::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (ServiceMode == EBTServiceActivationMode::BecomeRelevant)
	{
		ActivateAbility(OwnerComp);
	}
}

void UBTS_ActivateAbility::ActivateAbility(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr)
	{
		return;
	}
	
	APawn* OwnerPawn = AIController->GetPawn();

	if (OwnerPawn == nullptr)
	{
		return;
	}

	FGameplayEventData EventData;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerPawn, ActivationAbilityTag, EventData);
}
