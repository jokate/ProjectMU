// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/AttackSpawnSkill/MUGA_SpawnProjectile.h"

#include "Abilities/AT/AttackSpawnTask/MUAT_SpawnProjectile.h"

void UMUGA_SpawnProjectile::ActivateSkill()
{
	Super::ActivateSkill();

	//여기서 추가적인 처리 필요.
	FTransform SpawnTransform;
	
	SpawnTransform.SetLocation(GetOwningActorFromActorInfo()->GetActorLocation());
	SpawnTransform.SetRotation(FRotator(-90, SpawnTransform.Rotator().Yaw, 0).Quaternion());
	
	UMUAT_SpawnProjectile* Task = UMUAT_SpawnProjectile::SpawnProjectile(this, AttackEntityClass, SpawnTransform, SpawnWaitTime );

	if ( IsValid(Task) == true )
	{
		Task->OnSpawnActorFinished.AddDynamic(this, &UMUGA_SpawnProjectile::OnFinishedSpawn);
		Task->ReadyForActivation();
	}
}

void UMUGA_SpawnProjectile::OnFinishedSpawn()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
