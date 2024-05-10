// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_CheckVelocity.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementCompleted);

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_CheckVelocity : public UAbilityTask
{
	GENERATED_BODY()

public :
	UMUAT_CheckVelocity();
	
	static UMUAT_CheckVelocity* CreateNewTask(UGameplayAbility* InAbility);

protected:
	virtual void TickTask(float DeltaTime) override;
	
	virtual void Activate() override;

public :
	FOnMovementCompleted MoveCompleted;

	UPROPERTY()
	TObjectPtr<class ACharacter> CurrentCharacter;
};
