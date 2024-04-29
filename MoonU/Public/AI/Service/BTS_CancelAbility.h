// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTS_AbilityAction.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BTService.h"
#include "BTS_CancelAbility.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTS_CancelAbility : public UBTS_AbilityAction
{
	GENERATED_BODY()

public :
	virtual void OnActivateNode(UBehaviorTreeComponent& OwnerComp) override;
	
	UPROPERTY(EditAnywhere, Category = ActivationTag)
	FGameplayTagContainer DeactivationAbilityTags;
};
