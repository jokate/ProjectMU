// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/StateTree/Evaluator/MUAIPerceptionEvaluator.h"

#include "StateTreeExecutionContext.h"
#include "AI/MUAIController.h"
#include "Character/MUCharacterBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
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

	UEnvQueryManager* QueryManager = UEnvQueryManager::GetCurrent(AIController->GetWorld());

	if ( IsValid(QueryManager) == false )
	{
		return;
	} 
	
	FEnvQueryRequest Request(InstanceData.TargetingEQS, AIController);

	TSharedPtr<FEnvQueryResult> Result = QueryManager->RunInstantQuery(Request, EEnvQueryRunMode::Type::SingleResult);

	if ( Result.IsValid() == false )
	{
		return;
	}

	InstanceData.TargetActor = Result->GetItemAsActor(0);
}
