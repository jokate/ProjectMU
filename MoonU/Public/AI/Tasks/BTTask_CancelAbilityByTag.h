// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CancelAbilityByTag.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTTask_CancelAbilityByTag : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public :
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer NeedToCancelAbilityTags;
};
