// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Evaluator/MUAIPerceptionEvaluator.h"

#include "StateTreeExecutionContext.h"
#include "AI/MUAIController.h"
#include "Character/MUCharacterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

void FMUAIPerceptionEvaluator::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	UObject* ContextObject = Context.GetOwner();
	if ( IsValid(ContextObject) == false )
	{
		return;
	}

	AMUAIController* AIController = Cast<AMUAIController>(ContextObject);

	if (IsValid(AIController) == false)
	{
		return;
	}
	
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	InstanceData.Reset();
	
	UAIPerceptionComponent* PerceptionComponent = AIController->PerceptionComponent;

	if ( IsValid(PerceptionComponent) == false )
	{
		return;
	}

	TArray<AActor*> FoundActors;
	PerceptionComponent->GetKnownPerceivedActors(UAISense_Sight::StaticClass(), FoundActors);

	FoundActors = FoundActors.FilterByPredicate([](const AActor* Actor)
	{
		return Actor->IsA(AMUCharacterBase::StaticClass());
	});
	
	InstanceData.PendingTargetActors.Append(FoundActors);
}
