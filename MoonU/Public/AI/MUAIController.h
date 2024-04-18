// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Data/MUEnum.h"
#include "Perception/AIPerceptionTypes.h"
#include "MUAIController.generated.h"

UCLASS()
class MOONU_API AMUAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUAIController();

	void RunAI();

	void StopAI();
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void InitTestCode();

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

	virtual void HandleEventByPerceptionType(EPerceptionType Type);
protected :
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBehaviorTree> BTAsset;

	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<class UAISense>,TEnumAsByte<EPerceptionType>> PerceptionType;
	
	FTimerHandle TimerHandle;
};
