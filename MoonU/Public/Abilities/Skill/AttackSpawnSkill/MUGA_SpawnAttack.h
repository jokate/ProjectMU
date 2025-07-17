// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Skill/MUGA_IndicatorSkill.h"
#include "MUGA_SpawnAttack.generated.h"

class AMUAttackEntity;
/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_SpawnAttack : public UMUGA_IndicatorSkill
{
	GENERATED_BODY()

public :
	virtual void ActivateSkill() override;
	
public :
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf<AMUAttackEntity> AttackEntityClass;
};
