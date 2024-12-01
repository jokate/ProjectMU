// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTS_AbilityAction.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BTService.h"
#include "BTS_ActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTS_ActivateAbility : public UBTS_AbilityAction
{
	GENERATED_BODY()

protected :
	virtual void OnActivateNode(UBehaviorTreeComponent& OwnerComp) override;

	UPROPERTY(EditAnywhere, Category = AbilityActivation)
	TEnumAsByte<EAbilityActivationMode> ActivationMode;
	
	UPROPERTY(EditAnywhere, Category = AbilityActivation)
	FGameplayTagContainer ActivationAbilityTags;

	UPROPERTY(EditAnywhere, Category = AbilityActivation)
	TArray<int32> InputIDs;
};
