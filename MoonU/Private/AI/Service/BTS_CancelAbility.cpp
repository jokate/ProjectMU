// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_CancelAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

void UBTS_CancelAbility::OnActivateNode(UBehaviorTreeComponent& OwnerComp)
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

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerPawn);

	if (ASC == nullptr)
	{
		return;
	}

	ASC->CancelAbilities(&DeactivationAbilityTags);
}
