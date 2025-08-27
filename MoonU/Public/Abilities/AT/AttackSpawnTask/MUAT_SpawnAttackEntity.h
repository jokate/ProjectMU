// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Entity/AttackEntity/MUAttackEntity.h"
#include "MUAT_SpawnAttackEntity.generated.h"

/**
 * 
 */
class AMUAttackEntity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnActorFininshed);

UCLASS()
class MOONU_API UMUAT_SpawnAttackEntity : public UAbilityTask
{
	GENERATED_BODY()

public :
	static UMUAT_SpawnAttackEntity* StartSpawnAttackEntity( UGameplayAbility* OwningAbility, FName SkillName,
		FTransform InSpawnTransform, float InSpawnWaitTime = 0.f );

	virtual void Activate() override;

	UFUNCTION()
	virtual void SpawnAttackEntity();

	virtual void SetupInfoBeforeFinishSpawn( AMUAttackEntity* AttackEntity );
	
public :
	
	UPROPERTY( BlueprintAssignable )
	FOnSpawnActorFininshed OnSpawnActorFinished;

public :
	UPROPERTY()
	TWeakObjectPtr<AMUAttackEntity> SpawnedAttackEntity;

protected :
	UPROPERTY()
	FTransform SpawnTransform;

	UPROPERTY()
	FName SkillID = NAME_None;

	UPROPERTY()
	float SpawnWaitTime;
	
	FTimerHandle SpawnTimer;
};
