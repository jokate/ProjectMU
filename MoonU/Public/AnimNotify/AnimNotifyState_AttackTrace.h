// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AttackTrace.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UAnimNotifyState_AttackTrace : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	
public :
	UPROPERTY(EditAnywhere)
	FGameplayTag TriggerGameplayTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag EndTriggerGameplayTag;
};
