// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_SpawnAttackEntity.h"

#include "Entity/AttackEntity/MUAttackEntity.h"

UMUAT_SpawnAttackEntity* UMUAT_SpawnAttackEntity::StartSpawnAttackEntity(UGameplayAbility* OwningAbility,
                                                                         TSubclassOf<AMUAttackEntity> InClass, FTransform InSpawnTransform, float InSpawnWaitTime)
{
	UMUAT_SpawnAttackEntity* MyTask = NewAbilityTask<UMUAT_SpawnAttackEntity>(OwningAbility);

	MyTask->SpawnTransform = InSpawnTransform;
	MyTask->SpawnWaitTime = InSpawnWaitTime;
	MyTask->SpawnClass = InClass;

	return MyTask;
}

void UMUAT_SpawnAttackEntity::Activate()
{
	Super::Activate();

	if ( SpawnWaitTime <= 0.f )
	{
		SpawnAttackEntity();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &UMUAT_SpawnAttackEntity::SpawnAttackEntity, SpawnWaitTime, false);
	}
}

void UMUAT_SpawnAttackEntity::SpawnAttackEntity() const
{
	AMUAttackEntity* AttackEntity = GetWorld()->SpawnActorDeferred<AMUAttackEntity>(SpawnClass, SpawnTransform);

	if ( IsValid(AttackEntity) == false )
	{
		return;
	}

	AttackEntity->RegisterOwner( GetAvatarActor() );
	AttackEntity->FinishSpawning(SpawnTransform);

	if ( OnSpawnActorFinished.IsBound() )
	{
		OnSpawnActorFinished.Broadcast();
	}
}
