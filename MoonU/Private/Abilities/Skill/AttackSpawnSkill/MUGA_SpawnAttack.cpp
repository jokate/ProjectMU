// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/AttackSpawnSkill/MUGA_SpawnAttack.h"

#include "Entity/AttackEntity/MUAttackEntity.h"

void UMUGA_SpawnAttack::ActivateSkill()
{
	Super::ActivateSkill();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(TargetLocation);
	SpawnTransform.SetRotation(TargetRotation.Quaternion());
	AMUAttackEntity* AttackEntity = GetWorld()->SpawnActorDeferred<AMUAttackEntity>(AttackEntityClass, SpawnTransform);

	if ( IsValid(AttackEntity) == false )
	{
		return;
	}

	AttackEntity->RegisterOwner( CurrentActorInfo->OwnerActor.Get() );
	AttackEntity->FinishSpawning(SpawnTransform);
}
