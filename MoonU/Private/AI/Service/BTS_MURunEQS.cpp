// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTS_MURunEQS.h"

#include "EnvironmentQuery/EnvQueryManager.h"
#include "Interface/MUEnemy.h"


UBTS_MURunEQS::UBTS_MURunEQS(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Run EQS";

	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = true;

	QueryFinishedDelegate = FQueryFinishedSignature::CreateUObject(this, &UBTS_MURunEQS::OnQueryFinished);
}

void UBTS_MURunEQS::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	EQSRequest.InitForOwnerAndBlackboard(*this, GetBlackboardAsset());

	//확인해보니까 쿼리를 사용하기 Blackboard Key를 기반으로 쿼리를 사용하지 말아야 함.
	EQSRequest.bUseBBKeyForQueryTemplate = false;
}

void UBTS_MURunEQS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Baseline Is Descripted In UBTService_RunEQS
	AActor* QueryOwner = OwnerComp.GetOwner();
	AController* ControllerOwner = Cast<AController>(QueryOwner);
	if (ControllerOwner)
	{
		QueryOwner = ControllerOwner->GetPawn();
	}

	if (QueryOwner && EQSRequest.IsValid())
	{
		const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		FMUEQSServiceMemory* MyMemory = CastInstanceNodeMemory<FMUEQSServiceMemory>(NodeMemory);

		// Trigger new query only if the previous one has already finished
		if (MyMemory->RequestID == INDEX_NONE)
		{
			MyMemory->RequestID = EQSRequest.Execute(*QueryOwner, BlackboardComponent, QueryFinishedDelegate);
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTS_MURunEQS::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FMUEQSServiceMemory* EQSServiceMemory = CastInstanceNodeMemory<FMUEQSServiceMemory>(NodeMemory);

	if (EQSServiceMemory == nullptr) 
	{	
		UE_LOG(LogTemp, Log, TEXT("No Valid EQSService Memory"));
	}

	if ( EQSServiceMemory->RequestID != INDEX_NONE )
	{
		UWorld* World = OwnerComp.GetWorld();

		if (IsValid(World) == true)
		{
			//AISubsystem에 선언되어있음. 
			UEnvQueryManager* EQSManager = UEnvQueryManager::GetCurrent(World);
			if (IsValid(EQSManager) == true)
			{
				//해당 BT의 경우에는 NodeMemory를 넣어서 동작하는 방식 -> 내가 의도하고자 하는 ID를 넣어주는 것이 좋아보일지도.
				EQSManager->AbortQuery(EQSServiceMemory->RequestID);
			}

			//초기화 작업 수행.
			EQSServiceMemory->RequestID = INDEX_NONE;
		}
	}
}

//내가 사용하고자 하는메모리가 있으면, 이 메모리에 대해서 사용할 것을 정의한다.
//즉 해당 메모리에 대한 초기화 시, 어떻게 동작할 것인가에 대해서 정의한다고 생각하면 된다.
void UBTS_MURunEQS::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTMemoryInit::Type InitType) const
{
	FMUEQSServiceMemory* EQSMemory = CastInstanceNodeMemory<FMUEQSServiceMemory>(NodeMemory);
	if (EQSMemory == nullptr)
	{
		return;		
	}

	//메모리 영역에 대한 초기화 작업 수행.
	EQSMemory->RequestID = INDEX_NONE;
}

void UBTS_MURunEQS::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	//실패한 경우.
	if (Result->IsAborted())
	{
		return;
	}

	AActor* MyOwner = Cast<AActor>(Result->Owner.Get());
	if (APawn* PawnOwner = Cast<APawn>(MyOwner))
	{
		MyOwner = PawnOwner->GetController();
	}

	UBehaviorTreeComponent* BTComp = MyOwner ? MyOwner->FindComponentByClass<UBehaviorTreeComponent>() : NULL;
	if (!BTComp)
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Unable to find behavior tree to notify about finished query from %s!"), *GetNameSafe(MyOwner));
		return;
	}

	//현재 상황에 맞는 Request가 무엇인지에 대해서 가져오는 것, 즉 BT에서 해당 노드를 돌릴 건데
	//현재 돌리고 있는 노드 메모리에 저장된 Memory값을 가져온다.
	FMUEQSServiceMemory* MyMemory = CastInstanceNodeMemory<FMUEQSServiceMemory>(BTComp->GetNodeMemory(this, BTComp->FindInstanceContainingNode(this)));

	check(MyMemory);
	ensure(MyMemory->RequestID != INDEX_NONE);

	bool bSuccess = Result->IsSuccessful() && (Result->Items.Num() >= 1);
	if (bSuccess)
	{
		AActor* TargetActor = Result->GetItemAsActor(0);

		if ( IsValid(TargetActor) == false )
		{
			MyMemory->RequestID = INDEX_NONE;
			UE_LOG(LogTemp, Log, TEXT("Target Actor is Not Valid"));
			return;
		}

		IMUEnemy* Enemy = Cast<IMUEnemy>(MyOwner);

		if ( Enemy == nullptr )
		{
			MyMemory->RequestID = INDEX_NONE;
			UE_LOG(LogTemp, Log, TEXT("Enemy Interface cast Failed"))
			return;
		}

		Enemy->SetupTarget(TargetActor);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not Success"));
	}

	MyMemory->RequestID = INDEX_NONE;
}
