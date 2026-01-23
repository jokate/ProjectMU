// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_SetTimerAndWait.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnTimerFinished);

UCLASS()
class MOONU_API UMUAT_SetTimerAndWait : public UAbilityTask
{
	GENERATED_BODY()
	
public :
	static UMUAT_SetTimerAndWait* CreateTask(UGameplayAbility* TargetAbility, float TimerToAction);

	void OnTimerEnd();
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
public :
	FOnTimerFinished OnFinished;
	FTimerHandle WaitTimeHandle;
	
	float TimeToWait = 0.f;
};
