// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BTService.h"
#include "BTS_AbilityAction.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTS_AbilityAction : public UBTService
{
	GENERATED_BODY()

public :
	UBTS_AbilityAction();
	
protected :
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnActivateNode(UBehaviorTreeComponent& OwnerComp);

	UPROPERTY(EditAnywhere, Category = ServideMode)
	TEnumAsByte<EBTServiceActivationMode> ServiceMode;
};
