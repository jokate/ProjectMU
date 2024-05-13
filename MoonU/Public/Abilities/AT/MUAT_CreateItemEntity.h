// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_CreateItemEntity.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_CreateItemEntity : public UAbilityTask
{
	GENERATED_BODY()
	
public :
	static UMUAT_CreateItemEntity* CreateTask(UGameplayAbility* InAbility, FName InItemDropPoolID);

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	UPROPERTY()
	FName ItemDropPoolID;
};
