// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_LaunchCharacter.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLaunchFinished);

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_LaunchCharacter : public UAbilityTask
{
	GENERATED_BODY()

public :
	static UMUAT_LaunchCharacter* CreateTask(UGameplayAbility* InAbility, const FVector& DestinationVector);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	UFUNCTION()
	void OnLanded(const FHitResult& HitResult);
	
	UPROPERTY()
	FLaunchFinished OnLaunchCompleted;

protected :
	UPROPERTY()
	FVector DestVector;
};
