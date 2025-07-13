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

	switch (ActivationMode)
	{
	case ByEvent :
		{
			TArray<FGameplayTag> EventTags;
			StartAbilityTags.GetGameplayTagArray(EventTags);
			for (FGameplayTag& ActivationAbilityTag : EventTags)
			{
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ControllingPawn, ActivationAbilityTag, FGameplayEventData());	
			}	
		}
		break;

	case ByInputID :
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ControllingPawn);
			if (ASC == nullptr)
			{
				break;
			}
			
			FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromInputID(InputID);

			if ( Spec == nullptr)
			{
				break;
			}
			
			if (Spec->IsActive())
			{
				ASC->AbilitySpecInputPressed(*Spec);	
			}
			else
			{
				ASC->TryActivateAbility(Spec->Handle);
			}
		}
	default :
		UE_LOG(LogTemp, Warning, TEXT("INVALID!"));
		break;
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
	
	ASC->CancelAbilities(&StartAbilityTags);
	
	return Super::AbortTask(OwnerComp, NodeMemory);
}

