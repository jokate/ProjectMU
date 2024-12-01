// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_ActivateAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
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
	
	switch (ActivationMode)
	{
	case ByEvent :
		{
			TArray<FGameplayTag> EventTags;
			ActivationAbilityTags.GetGameplayTagArray(EventTags);
			for (FGameplayTag& ActivationAbilityTag : EventTags)
			{
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerPawn, ActivationAbilityTag, FGameplayEventData());	
			}	
		}
		break;

	case ByInputID :
		{
			UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerPawn);
			if (ASC == nullptr)
			{
				break;
			}

			for (int32 InputID : InputIDs)
			{
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
	default :
		UE_LOG(LogTemp, Warning, TEXT("INVALID!"));
		break;
	}
	
}
