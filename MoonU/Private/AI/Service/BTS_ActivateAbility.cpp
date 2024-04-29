﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_ActivateAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"

void UBTS_ActivateAbility::OnActivateNode(UBehaviorTreeComponent& OwnerComp)
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
