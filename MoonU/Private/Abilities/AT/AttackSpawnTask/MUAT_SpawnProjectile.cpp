// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/AttackSpawnTask/MUAT_SpawnProjectile.h"
#include "Entity/AttackEntity/MUAttackEntity.h"
#include "Entity/AttackEntity/MUProjectileEntity.h"

UMUAT_SpawnProjectile* UMUAT_SpawnProjectile::SpawnProjectile(UGameplayAbility* OwningAbility,
                                                              FName InSkillID,  FTransform InSpawnTransform, float InSpawnWaitTime)
{
	UMUAT_SpawnProjectile* MyTask = NewAbilityTask<UMUAT_SpawnProjectile>(OwningAbility);

	MyTask->SpawnTransform = InSpawnTransform;
	MyTask->SpawnWaitTime = InSpawnWaitTime;
	MyTask->SkillID = InSkillID;

	return MyTask;
}

void UMUAT_SpawnProjectile::SetupInfoBeforeFinishSpawn(AMUAttackEntity* AttackEntity)
{
	Super::SetupInfoBeforeFinishSpawn(AttackEntity);
}
