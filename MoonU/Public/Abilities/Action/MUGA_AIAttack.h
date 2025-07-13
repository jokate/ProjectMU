// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_Attack.h"
#include "Interface/RetriggerAbility.h"
#include "MUGA_AIAttack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_AIAttack : public UMUGA_Attack, public IRetriggerAbility
{
	GENERATED_BODY()

public :
	virtual void RetriggerAbility() override;
};
