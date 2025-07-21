// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectComponent.h"
#include "MUGameplayEffectComponent_Montage.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGameplayEffectComponent_Montage : public UGameplayEffectComponent
{
	GENERATED_BODY()

public :
	UPROPERTY( EditDefaultsOnly, meta = (DisplayName = "Montage To Play"))
	TObjectPtr<UAnimMontage> MontageToPlay;
};
