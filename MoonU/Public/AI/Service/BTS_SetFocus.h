// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetFocus.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTS_SetFocus : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected :
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere)
	uint8 bSetFocus : 1;
};
