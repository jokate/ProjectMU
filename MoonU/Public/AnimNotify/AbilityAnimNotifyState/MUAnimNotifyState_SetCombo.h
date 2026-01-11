// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUAnimNotifyState_Ability.h"
#include "MUAnimNotifyState_SetCombo.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAnimNotifyState_SetCombo : public UMUAnimNotifyState_Ability
{
	GENERATED_BODY()

public :
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	FName NextSection;
};
