// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_AddTagTemporary.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_AddTagTemporary : public UAbilityTask
{
	GENERATED_BODY()

public :
	static UMUAT_AddTagTemporary* CreateTask( UGameplayAbility* Ability, FGameplayTagContainer AddTag );

	virtual void Activate() override;
	
public :
	UPROPERTY()
	FGameplayTagContainer AddingTag;
};
