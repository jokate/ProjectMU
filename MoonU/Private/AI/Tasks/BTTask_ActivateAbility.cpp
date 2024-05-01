﻿// Fill out your copyright notice in the Description page of Project Settings.


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

	switch (ActivationMode)
	{
	case ByEvent :
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ControllingPawn, StartAbilityTag, FGameplayEventData());
		break;

	case ByInputID :
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);
			if (ASC == nullptr)
			{
				break;
			}
			
			FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputID);

			if (Spec->IsActive())
			{
				ASC->AbilitySpecInputPressed(*Spec);	
			}
			else
			{
				ASC->TryActivateAbility(Spec->Handle);
			}
		}
	}
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_ActivateAbility::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);

	const FGameplayTagContainer TagContainer(StartAbilityTag);
	ASC->CancelAbilities(&TagContainer);
	
	return Super::AbortTask(OwnerComp, NodeMemory);
}

