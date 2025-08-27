// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUAT_SpawnAttackEntity.h"

#include "MUAT_SpawnProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAT_SpawnProjectile : public UMUAT_SpawnAttackEntity
{
	GENERATED_BODY()

public :
	UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"), Category="Ability|Tasks")
	static UMUAT_SpawnProjectile* SpawnProjectile(UGameplayAbility* OwningAbility, FName InSkillID, FTransform InSpawnTransform, float InSpawnWaitTime = 0.f  );

protected :
	
	virtual void SetupInfoBeforeFinishSpawn(AMUAttackEntity* AttackEntity) override;
};
