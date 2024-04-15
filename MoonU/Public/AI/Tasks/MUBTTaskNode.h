// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MUBTTaskNode.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTaskFinishedGAS, const FGameplayEventData* EventData);
DECLARE_MULTICAST_DELEGATE(FOnTaskFinished);

UCLASS()
class MOONU_API UMUBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
protected :
	FOnTaskFinishedGAS TaskFinishedGAS;

	FOnTaskFinished TaskFinished;
};
