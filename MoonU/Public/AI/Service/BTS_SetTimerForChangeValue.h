// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetTimerForChangeValue.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnTimerEnd)

UCLASS()
class MOONU_API UBTS_SetTimerForChangeValue : public UBTService
{
	GENERATED_BODY()

	UBTS_SetTimerForChangeValue();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void SetTimerForChangeValue(TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp);

	void BroadcastEvent();

	UPROPERTY(EditAnywhere, Category = TimerSetter)
	FBlackboardKeySelector SelectedKey;
	
	UPROPERTY(EditAnywhere, Category = TimerSetter)
	float TimerInterval;

	UPROPERTY(EditAnywhere, Category = TimerSetter)
	TEnumAsByte<EBlackboardKeyData> DataTypeToChange;

	UPROPERTY(EditAnywhere, Category = TimerSetter)
	float ChangeValFloat;

	UPROPERTY(EditAnywhere, Category = TimerSetter)
	int32 ChangeValInt;

	UPROPERTY(EditAnywhere, Category = TimerSetter)
	FVector ChangeValVector;
	
	UPROPERTY(EditAnywhere, Category = TimerSetter)
	bool ChangeValBool;

	FOnTimerEnd OnTimerEnd;
	
	FTimerHandle ChangeTimer;
};
