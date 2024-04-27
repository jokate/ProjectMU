// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AI/AIEnum.h"
#include "Navigation/PathFollowingComponent.h"
#include "MUAT_MoveToAI.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIMoveCompleted);
/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_MoveToAI : public UAbilityTask
{
	GENERATED_BODY()

public :
	
	static UMUAT_MoveToAI* CreateTask(UGameplayAbility* OwningAbility, const FName& InTargetKey, EBlackboardKeyData InBlackboardKeyType, float InAcceptanceRadius);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;
	
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

	FAIMoveCompleted MoveCompleted;
protected:
	UPROPERTY()
	FName TargetKey;

	UPROPERTY()
	TEnumAsByte<EBlackboardKeyData> BlackboardKeyData;

	UPROPERTY()
	float AcceptanceRadius;
	
};

