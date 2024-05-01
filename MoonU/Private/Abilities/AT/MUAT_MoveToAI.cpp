// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_MoveToAI.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMUAT_MoveToAI* UMUAT_MoveToAI::CreateTask(UGameplayAbility* OwningAbility, const FName& InTargetKey,
                                           EBlackboardKeyData InBlackboardKeyType, float InAcceptanceRadius)
{
	UMUAT_MoveToAI* NewTask = NewAbilityTask<UMUAT_MoveToAI>(OwningAbility);
	NewTask->TargetKey = InTargetKey;
	NewTask->BlackboardKeyData = InBlackboardKeyType;
	NewTask->AcceptanceRadius = InAcceptanceRadius;

	return NewTask;
}

void UMUAT_MoveToAI::Activate()
{
	Super::Activate();

	AIMove();
	
	APawn* OwnerPawn = CastChecked<APawn>(GetAvatarActor());
	AAIController* AIController = CastChecked<AAIController>(OwnerPawn->GetController());
	
	AIController->ReceiveMoveCompleted.AddDynamic(this, &UMUAT_MoveToAI::OnMoveCompleted);

	SetWaitingOnAvatar();
}

void UMUAT_MoveToAI::OnDestroy(bool bInOwnerFinished)
{
	APawn* OwnerPawn = CastChecked<APawn>(GetAvatarActor());
	AAIController* AIController = Cast<AAIController>(OwnerPawn->GetController());

	if (AIController)
	{
		AIController->StopMovement();
		AIController->ReceiveMoveCompleted.RemoveAll(this);
	}
	
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_MoveToAI::OnMoveCompleted(FAIRequestID RequestID, const EPathFollowingResult::Type Result)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		MoveCompleted.Broadcast(RequestID, Result);
	}
}

void UMUAT_MoveToAI::AIMove()
{
	APawn* OwnerPawn = CastChecked<APawn>(GetAvatarActor());
	AAIController* AIController = CastChecked<AAIController>(OwnerPawn->GetController());
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	switch (BlackboardKeyData)
	{
	case ActorType :
		{
			AActor* TargetActor = CastChecked<AActor>(BBComponent->GetValueAsObject(TargetKey));
			AIController->MoveToActor(TargetActor, AcceptanceRadius, false);
			break;	
		}
	case VectorType:
		{
			FVector TargetLocation = BBComponent->GetValueAsVector(TargetKey);
			AIController->MoveToLocation(TargetLocation, AcceptanceRadius, false);
			break;	
		}
	default:
		UE_LOG(LogTemp, Warning, TEXT("Wrong Type init"));
		break;
	}
}
