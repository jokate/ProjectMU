// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/AttackSpawnSkill/MUGA_SpawnAttack.h"

#include "Abilities/AT/MUAT_SpawnAttackEntity.h"
#include "Entity/AttackEntity/MUAttackEntity.h"

void UMUGA_SpawnAttack::ActivateSkill()
{
	Super::ActivateSkill();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(TargetLocation);
	SpawnTransform.SetRotation(TargetRotation.Quaternion());
	
	UMUAT_SpawnAttackEntity* Task = UMUAT_SpawnAttackEntity::StartSpawnAttackEntity(this, AttackEntityClass, SpawnTransform, SpawnWaitTime );

	if ( IsValid(Task) == true )
	{
		Task->OnSpawnActorFinished.AddDynamic(this, &UMUGA_SpawnAttack::OnFinishedSpawn);
		Task->ReadyForActivation();
	}
}

void UMUGA_SpawnAttack::OnFinishedSpawn()
{
	bool bReplicatedEndAbility = true;
    bool bWasCancelled = false;
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
