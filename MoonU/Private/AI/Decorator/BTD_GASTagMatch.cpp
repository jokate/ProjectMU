// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_GASTagMatch.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

bool UBTD_GASTagMatch::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* GameplayTagActor = OwnerComp.GetAIOwner()->GetPawn();

	if (GameplayTagActor == nullptr)
	{
		return false;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GameplayTagActor);

	if (ASC == nullptr)
	{
		return false;
	}

	switch (TagsToMatch)
	{
	case EGameplayContainerMatchType::All:
		return ASC->HasAllMatchingGameplayTags(GameplayTags);

	case EGameplayContainerMatchType::Any:
		return ASC->HasAnyMatchingGameplayTags(GameplayTags);

	default:
		{
			UE_LOG(LogBehaviorTree, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(TagsToMatch));
			return false;
		}
	}
}
