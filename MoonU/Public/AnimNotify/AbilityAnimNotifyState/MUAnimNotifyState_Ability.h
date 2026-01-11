// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MUAnimNotifyState_Ability.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class MOONU_API UMUAnimNotifyState_Ability : public UAnimNotifyState
{
	GENERATED_BODY()

public :
	virtual UGameplayAbility* GetCurrentAbility(USkeletalMeshComponent* MeshComponent) const;
};
