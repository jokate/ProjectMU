// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
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
	static UMUAT_SpawnAttackEntity* StartSpawnAttackEntity( UGameplayAbility* OwningAbility, TSubclassOf<AMUAttackEntity> InClass,
		FTransform InSpawnTransform, float InSpawnWaitTime = 0.f );

	virtual void Activate() override;

	UFUNCTION()
	void SpawnAttackEntity() const;
	
public :
	
	UPROPERTY( BlueprintAssignable )
	FOnSpawnActorFininshed OnSpawnActorFinished;

protected :
	UPROPERTY()
	FTransform SpawnTransform;

	UPROPERTY()
	TSubclassOf<AMUAttackEntity> SpawnClass;

	UPROPERTY()
	float SpawnWaitTime;
	
	FTimerHandle SpawnTimer;
};
