// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MUGA_HitReaction.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_HitReaction : public UGameplayAbility
{
	GENERATED_BODY()

	
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAnimMontage> MontageToPlay;
};
