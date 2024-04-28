// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIEnum.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UBTTask_ChangeBlackboardValue : public UBTTaskNode
{
	GENERATED_BODY()

public :
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

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
};
