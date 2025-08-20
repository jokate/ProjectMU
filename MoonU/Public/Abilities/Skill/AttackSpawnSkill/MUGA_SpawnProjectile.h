// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Skill/MUGA_IndicatorSkill.h"
#include "MUGA_SpawnProjectile.generated.h"

class AMUAttackEntity;
/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_SpawnProjectile : public UMUGA_IndicatorSkill
{
	GENERATED_BODY()

public :
	virtual void ActivateSkill() override;

	UFUNCTION()
	virtual void OnFinishedSpawn();
	
public :
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<AMUAttackEntity> AttackEntityClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float SpawnWaitTime = 0.f;
};
