// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "BTS_MURunEQS.generated.h"

/**
 * 
 */
struct FMUEQSServiceMemory
{
	//카피해서 따라해봅니다. 단, 해당 부분은 이유에 대해서 파악이 필요합니다.
	int32 RequestID;
};


UCLASS()
class MOONU_API UBTS_MURunEQS : public UBTService
{
	GENERATED_BODY()

public :
	UPROPERTY(Category = EQS, EditAnywhere)
	FEQSParametrizedQueryExecutionRequest EQSRequest;
	
	FQueryFinishedSignature QueryFinishedDelegate;

public :
	UBTS_MURunEQS(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	
protected :
	void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);
};
