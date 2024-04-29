// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_AbilityAction.h"

UBTS_AbilityAction::UBTS_AbilityAction()
{
	bTickIntervals = true;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTS_AbilityAction::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ServiceMode == EBTServiceActivationMode::TickNode)
	{
		OnActivateNode(OwnerComp);
	}
}

void UBTS_AbilityAction::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ServiceMode == EBTServiceActivationMode::CeaseRelevant)
	{
		OnActivateNode(OwnerComp);
	}
	
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

void UBTS_AbilityAction::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	if (ServiceMode == EBTServiceActivationMode::BecomeRelevant)
	{
		OnActivateNode(OwnerComp);
	}
}

void UBTS_AbilityAction::OnActivateNode(UBehaviorTreeComponent& OwnerComp)
{
	//Need To Define When Inherited
}
