// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_GASTagMatch.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_GASTagMatch::UBTD_GASTagMatch()
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

bool UBTD_GASTagMatch::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BBComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		return false;
	}

	AActor* TargetActor = Cast<AActor>(BBComponent->GetValueAsObject(TagCheckTarget.SelectedKeyName));

	if (TargetActor == nullptr)
	{
		return false;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

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

void UBTD_GASTagMatch::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BBComponent->GetValueAsObject(TagCheckTarget.SelectedKeyName));

	if (TargetActor == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (ASC == nullptr)
	{
		return;
	}

	for (const FGameplayTag& CurrentTag : GameplayTags)
	{
		ASC->RegisterGameplayTagEvent(CurrentTag, EGameplayTagEventType::Type::AnyCountChange).AddUObject(this, &UBTD_GASTagMatch::OnGameplayTagChanged, TWeakObjectPtr<UBehaviorTreeComponent>(&OwnerComp), NodeMemory);	
	}
}

void UBTD_GASTagMatch::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComponent = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(BBComponent->GetValueAsObject(TagCheckTarget.SelectedKeyName));

	if (TargetActor == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (ASC == nullptr)
	{
		return;
	}

	for (const FGameplayTag& CurrentTag : GameplayTags)
	{
		ASC->RegisterGameplayTagEvent(CurrentTag, EGameplayTagEventType::Type::AnyCountChange).RemoveAll(this);
	}
}

void UBTD_GASTagMatch::OnGameplayTagChanged(const FGameplayTag InTag, int32 NewCount, TWeakObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent, uint8* NodeMemory)
{
	if (!BehaviorTreeComponent.IsValid())
	{
		return;
	}

	ConditionalFlowAbort(*BehaviorTreeComponent, EBTDecoratorAbortRequest::ConditionResultChanged);
}
