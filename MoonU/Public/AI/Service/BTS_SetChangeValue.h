// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_SetChangeValue.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTS_SetChangeValue : public UBTService
{
	GENERATED_BODY()

	UBTS_SetChangeValue();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	void ChangeValue(UBehaviorTreeComponent& OwnerComp);
	
	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FBlackboardKeySelector SelectedKey;
	
	UPROPERTY(EditAnywhere, Category = ValueSetter)
	TEnumAsByte<EBlackboardKeyData> DataTypeToChange;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	float ChangeValFloat;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	int32 ChangeValInt;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FVector ChangeValVector;
	
	UPROPERTY(EditAnywhere, Category = ValueSetter)
	bool ChangeValBool;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FName EnumName;

	UPROPERTY(EditAnywhere, Category = ValueSetter)
	FName EnumValue;

	UPROPERTY(EditAnywhere, Category = ActivationMode)
	bool bBecomeOrCeased;
};
