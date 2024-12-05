﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_MoveToAI.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/MUEnemy.h"

UMUAT_MoveToAI* UMUAT_MoveToAI::CreateTask(UGameplayAbility* OwningAbility, ETargetActivationType TargetActivationType, float InAcceptanceRadius)
{
	UMUAT_MoveToAI* NewTask = NewAbilityTask<UMUAT_MoveToAI>(OwningAbility);
	NewTask->ActivationKeyType = TargetActivationType;
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

	IMUEnemy* MUEnemy = Cast<IMUEnemy>(OwnerPawn);

	if (MUEnemy == nullptr)
	{
		return;
	}
	
	AAIController* AIController = CastChecked<AAIController>(OwnerPawn->GetController());
	switch (ActivationKeyType)
	{
	case Actor:
		{
			AActor* TargetActor = MUEnemy->GetActorTarget();
			
			if (IsValid(TargetActor) == false)
			{
				return;
			}
			
			AIController->MoveToActor(TargetActor, AcceptanceRadius, false);
		}
		break;	
	case Location : 
		{
			FVector TargetLocation = MUEnemy->GetTargetLocation();
			AIController->MoveToLocation(TargetLocation, AcceptanceRadius, false);
		}
		break;	
	default:
		UE_LOG(LogTemp, Warning, TEXT("Wrong Type init"));
		break;
	}
}
