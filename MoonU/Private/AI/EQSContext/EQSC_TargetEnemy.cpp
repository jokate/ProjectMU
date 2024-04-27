// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQSContext/EQSC_TargetEnemy.h"

#include "AIController.h"
#include "AI/MUAIDefines.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

void UEQSC_TargetEnemy::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	UObject* QuerierObject = QueryInstance.Owner.Get();

	if (QuerierObject == nullptr)
	{
		return;
	}

	APawn* QueryPawn = Cast<APawn>(QuerierObject);

	if (QueryPawn == nullptr)
	{
		return;
	}


	AAIController* AIController = Cast<AAIController>(QueryPawn->GetController());

	if (AIController == nullptr)
	{
		return;
	}

	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	if (BBComponent == nullptr)
	{
		return;
	}

	UObject* Object = BBComponent->GetValueAsObject(MU_AI_TARGET);

	if (Object)
	{
		AActor* TargetActor = Cast<AActor>(Object);

		const FVector& TargetActorLocation = TargetActor->GetActorLocation();

		if (FAISystem::IsValidLocation(TargetActorLocation))
		{
			UEnvQueryItemType_Point::SetContextHelper(ContextData, TargetActorLocation);
		}
	}
}
