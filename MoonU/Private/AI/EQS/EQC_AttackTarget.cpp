// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EQC_AttackTarget.h"

#include "AIController.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEQC_AttackTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	UObject* QuerierObject = QueryInstance.Owner.Get();

	if (QuerierObject == nullptr)
	{
		return;
	}

	AActor* QuerierActor = Cast<AActor>(QuerierObject);

	if (QuerierActor == nullptr)
	{
		return;
	}

	AAIController* AIController = UAIBlueprintHelperLibrary::GetAIController(QuerierActor);

	if (AIController == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (BlackboardComponent == nullptr)
	{
		return;
	}

	UObject* TargetObject = BlackboardComponent->GetValueAsObject(MU_AI_TARGET);

	if (TargetObject == nullptr)
	{
		return;
	}

	AActor* InActor = Cast<AActor>(TargetObject);

	if (InActor)
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, InActor);
	}
}
