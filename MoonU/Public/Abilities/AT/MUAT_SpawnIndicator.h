// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_SpawnIndicator.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_SpawnIndicator : public UAbilityTask
{
	GENERATED_BODY()

public:
	static UMUAT_SpawnIndicator* CreateTask( UGameplayAbility* OwningAbility, FName InSkillID );

	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;	
	
public :
	FName SkillID = NAME_None;
};
