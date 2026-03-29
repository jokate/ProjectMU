// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/AT/AttackSpawnTask/MUAT_SpawnAttackEntity.h"

#include "Components/MUCharacterRecordComponent.h"
#include "Data/MUDataPrimaryAsset.h"
#include "Entity/AttackEntity/MUAttackEntity.h"
#include "Entity/AttackEntity/Reactor/MUAttackEntityReactor.h"
#include "Entity/AttackEntity/Record/MUAttackEntityRecord.h"
#include "Framework/MUGameMode.h"
#include "Library/MUFunctionLibrary.h"

UMUAT_SpawnAttackEntity* UMUAT_SpawnAttackEntity::StartSpawnAttackEntity(UGameplayAbility* OwningAbility,
                                                                         FName SkillName, FTransform InSpawnTransform, float InSpawnWaitTime)
{
	UMUAT_SpawnAttackEntity* MyTask = NewAbilityTask<UMUAT_SpawnAttackEntity>(OwningAbility);

	MyTask->SpawnTransform = InSpawnTransform;
	MyTask->SpawnWaitTime = InSpawnWaitTime;
	MyTask->SkillID = SkillName;

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

void UMUAT_SpawnAttackEntity::SpawnAttackEntity()
{
	UMUDataPrimaryAsset* DataPrimaryAsset = UMUFunctionLibrary::GetDataPrimaryAsset(this);

	if ( IsValid(DataPrimaryAsset) == false )
	{
		return;
	}
	
	FMUAttackEntityData AttackEntityData;
	if ( UMUFunctionLibrary::GetRegistryData<FMUAttackEntityData>(this, DataPrimaryAsset->AttackEntityRegistryType, SkillID, AttackEntityData) == false )
	{
		return;
	}
	
	AMUGameMode* GM = GetWorld()->GetAuthGameMode<AMUGameMode>();

	if ( IsValid(GM) == false )
	{
		return;
	}

	AActor* PoolingObject = GM->GetPoolingObject(SkillID, SpawnTransform);
	
	AMUAttackEntity* AttackEntity = Cast<AMUAttackEntity>(PoolingObject);

	if ( IsValid(AttackEntity) == false )
	{
		return;
	}
	
	SetupInfoBeforeFinishSpawn(AttackEntity);

	if ( AMUAttackEntityReactor* EntityReactor = Cast<AMUAttackEntityReactor>(AttackEntity))
	{
		EntityReactor->ActivateObject(SpawnTransform);
	}

	if ( AMUAttackEntityRecord* EntityRecord = Cast<AMUAttackEntityRecord>(AttackEntity) )
	{
		AActor* OwnerActor = GetOwnerActor();

		if (IsValid(OwnerActor) == true )
		{
			UMUCharacterRecordComponent* RecordComponent = OwnerActor->GetComponentByClass<UMUCharacterRecordComponent>();

			if ( IsValid(RecordComponent) == true )
			{
				EntityRecord->AllocateRecord(RecordComponent->RecordDatas);
			}
		}
	}
	
	AttackEntity->SetLifeSpan(AttackEntityData.LifeSpan);

	
	SpawnedAttackEntity = AttackEntity;
	
	if ( OnSpawnActorFinished.IsBound() )
	{
		OnSpawnActorFinished.Broadcast();
	}
}

void UMUAT_SpawnAttackEntity::SetupInfoBeforeFinishSpawn(AMUAttackEntity* AttackEntity)
{
	AttackEntity->RegisterOwner( GetAvatarActor() );
}
