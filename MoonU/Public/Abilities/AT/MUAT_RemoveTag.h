// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_RemoveTag.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_RemoveTag : public UAbilityTask
{
	GENERATED_BODY()

public :
	static UMUAT_RemoveTag* CreateTask( UGameplayAbility* GameplayAbility, FGameplayTagContainer TagContainer );

	virtual void Activate() override;
	
public :
	UPROPERTY()
	FGameplayTagContainer RemoveTagContainer;
};
