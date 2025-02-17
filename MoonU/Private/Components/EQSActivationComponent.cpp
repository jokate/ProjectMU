// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EQSActivationComponent.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"

//해당 컴포넌트는 BTService_RunEQS의 기능을 컴포넌트화 시켰습니다.

UEQSActivationComponent::UEQSActivationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	QueryFinishedDelegate = FQueryFinishedSignature::CreateUObject(this, &UEQSActivationComponent::OnQueryFinished);

	StoreValueFunctions.Add(EBlackboardKeyData::ActorType, FUpdateBlackboardData::CreateUObject(this, &UEQSActivationComponent::StoreBlackboardActor));
	StoreValueFunctions.Add(EBlackboardKeyData::VectorType, FUpdateBlackboardData::CreateUObject(this, &UEQSActivationComponent::StoreBlackboardLocation));
}

void UEQSActivationComponent::BeginPlay()
{
	Super::BeginPlay();
	QueryRequestID = INDEX_NONE;
}

void UEQSActivationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActivateEQS();
}
bool UEQSActivationComponent::ActivateEQS()
{
	AAIController* Controller = GetOwner<AAIController>();

	if ( IsValid(Controller) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller Is Not Valid!"));
		return false;
	}

	APawn* QueryOwner = Controller->GetPawn();

	if ( IsValid(QueryOwner) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("Query Owner Is Not Valid"));
		return false;
	}

	if (EQSRequest.IsValid() == false )
	{
		UE_LOG(LogTemp, Error, TEXT("EQS Request Is Not Valid"));
		return false;
	}

	const UBlackboardComponent* BBComp = Controller->GetBlackboardComponent();

	if ( IsValid(BBComp) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("Blackboard Component Is Not Valid"));
		return false;	
	}

	if (QueryRequestID != INDEX_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Query Request is Already Activated"));
		return false;
	}
	
	QueryRequestID = EQSRequest.Execute(*QueryOwner, BBComp, QueryFinishedDelegate);
	return true;
}

void UEQSActivationComponent::InitializeEQSActivationComponent(UBlackboardData* BlackboardData)
{
	AActor* OwnerActor = GetOwner();

	if ( IsValid(OwnerActor) == false)
	{
		return;
	}

	EQSRequest.InitForOwnerAndBlackboard(*OwnerActor, BlackboardData);
}

void UEQSActivationComponent::OnQueryFinished(TSharedPtr<FEnvQueryResult> QueryResult)
{
	if (QueryResult->IsAborted() == true) 
	{
		UE_LOG(LogTemp, Warning, TEXT("EQS Aborted!"));
		return;
	}

	AActor* Owner = Cast<AActor>(QueryResult->Owner.Get());

	if ( IsValid(Owner) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("Owner Is Not Valid"));
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(Owner);

	if ( IsValid(OwnerPawn) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerPawn Is Not Valid"));
		return;
	}

	AAIController* Controller = OwnerPawn->GetController<AAIController>();

	if ( IsValid(Controller) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller Is Not Valid"));
		return;		
	}
	
	bool bSuccess = QueryResult->IsSuccessful() && (QueryResult->Items.Num() >= 1);
	
	UBlackboardComponent* BBComp = Controller->GetBlackboardComponent();
	if (IsValid(BBComp) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("No BBComp"));
		return;
	}
	if (bSuccess == true)
	{
		if (StoreValueFunctions.Find(BlackboardKey.BlackboardKeyType))
		{
			bSuccess = StoreValueFunctions[BlackboardKey.BlackboardKeyType].Execute(QueryResult->RawData.GetData() + QueryResult->Items[0].DataOffset);	
		}
		
		if (bSuccess == false)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed To Store Blackboard Data"));
		}
	}
	else if (bUpdateBBOnFail)
	{
		BBComp->ClearValue(BlackboardKey.BlackboardKeyName);
	}
	
	QueryRequestID = INDEX_NONE;
}

//Abort 시킬 목적으로 State 전환.
void UEQSActivationComponent::OnStateChanged()
{
	
}

bool UEQSActivationComponent::StoreBlackboardLocation(uint8* BlackboardData)
{
	AAIController* AIController = GetOwner<AAIController>();

	if ( IsValid(AIController) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller Is Not Valid"));
		return false;
	}

	UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();

	if ( IsValid(BBComp) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("BBComp Is Not Valid"));
		return false;
	}

	const FVector Vector = static_cast<FVector>(*BlackboardData);
	
	BBComp->SetValueAsVector(BlackboardKey.BlackboardKeyName, Vector);

	return true;
}

bool UEQSActivationComponent::StoreBlackboardActor(uint8* BlackboardData)
{
	AAIController* AIController = GetOwner<AAIController>();

	if ( IsValid(AIController) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller Is Not Valid"));
		return false;
	}

	UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();

	if ( IsValid(BBComp) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("BBComp Is Not Valid"));
		return false;
	}

	AActor* ActorPtr = reinterpret_cast<AActor*>(BlackboardData);

	if (IsValid(ActorPtr) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor Ptr Is Not Valid"));
		return false;
	}
	
	BBComp->SetValueAsObject(BlackboardKey.BlackboardKeyName, ActorPtr);

	return true;
}
