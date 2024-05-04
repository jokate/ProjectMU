// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_CheckGoldenTime.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGoldenTimeSatisFied);

UCLASS()
class MOONU_API UMUAT_CheckGoldenTime : public UAbilityTask
{
	GENERATED_BODY()
	

public :
	UMUAT_CheckGoldenTime();

	static UMUAT_CheckGoldenTime* CreateNewTask(UGameplayAbility* InAbility, float InGoldenTimeRate);

	virtual void Activate() override;
	
	virtual void OnDestroy(bool bInOwnerFinished) override;
	
	FGoldenTimeSatisFied GoldenTimeSatisFied;
protected :
	virtual void TickTask(float DeltaTime) override;

	UFUNCTION()
	void OnTimeWindChanged(bool InTimeChanged);

	UPROPERTY()
	uint8 bGoldenTimeTicking : 1;
	
	UPROPERTY()
	float GoldenTimeRate;

	UPROPERTY()
	float CurrentGoldenTime = 0.f;
};
