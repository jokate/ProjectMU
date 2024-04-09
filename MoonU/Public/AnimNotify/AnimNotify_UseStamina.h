// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_UseStamina.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UAnimNotify_UseStamina : public UAnimNotify
{
	GENERATED_BODY()
public : 
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere)
	float StaminaToUse;
};
