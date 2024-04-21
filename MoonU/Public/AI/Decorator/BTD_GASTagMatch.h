// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_GASTagMatch.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTD_GASTagMatch : public UBTDecorator
{
	GENERATED_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	UPROPERTY(EditAnywhere, Category=GameplayTagCheck)
	EGameplayContainerMatchType TagsToMatch;

	UPROPERTY(EditAnywhere, Category=GameplayTagCheck)
	FGameplayTagContainer GameplayTags;
	
};
