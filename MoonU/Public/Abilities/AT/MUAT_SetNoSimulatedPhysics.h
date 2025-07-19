// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_SetNoSimulatedPhysics.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_SetNoSimulatedPhysics : public UAbilityTask
{
	GENERATED_BODY()

public :
	static UMUAT_SetNoSimulatedPhysics* CreateTask( UGameplayAbility* OwningAbility );

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;
};
