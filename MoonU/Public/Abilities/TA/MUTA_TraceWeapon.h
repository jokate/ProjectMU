// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUTA_Trace.h"
#include "MUTA_TraceWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API AMUTA_TraceWeapon : public AMUTA_Trace
{
	GENERATED_BODY()
	
	AMUTA_TraceWeapon();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void TraceStart() override;

	virtual FGameplayAbilityTargetDataHandle MakeTargetData() override;
	UPROPERTY()
	FName WeaponSocketName;
};
