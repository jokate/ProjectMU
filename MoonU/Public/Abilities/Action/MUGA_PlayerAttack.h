// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUGA_Attack.h"
#include "MUGA_PlayerAttack.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_PlayerAttack : public UMUGA_Attack
{
	GENERATED_BODY()

public :
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
};
