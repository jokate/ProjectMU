// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MUStruct.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EQSActivationComponent.generated.h"

DECLARE_DELEGATE_RetVal_OneParam( bool, FUpdateBlackboardData, uint8*);

class UEnvQuery;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UEQSActivationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEQSActivationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	bool ActivateEQS();

	void InitializeEQSActivationComponent(UBlackboardData* BlackboardData);

	void OnStateChanged();

	bool StoreBlackboardLocation(uint8* BlackboardData);

	bool StoreBlackboardActor(uint8* BlackboardData);
	
protected :
	
	void OnQueryFinished(TSharedPtr<FEnvQueryResult> QueryResult);
	
public :
	// 결국에 해당 부분에 대해서 다중 교체가 이루어져야 함.
	UPROPERTY(Category = EQS, EditAnywhere)
	FEQSParametrizedQueryExecutionRequest EQSRequest;

	UPROPERTY(Category = EQS, EditAnywhere)
	bool bUpdateBBOnFail = false;

	FQueryFinishedSignature QueryFinishedDelegate;

	UPROPERTY(EditAnywhere, Category = "EQS|BlackBoard")
	FAIBlackboardKey BlackboardKey;

protected :
	TMap<TEnumAsByte<EBlackboardKeyData>, FUpdateBlackboardData> StoreValueFunctions;

private:
	int32 QueryRequestID = 0;
};
