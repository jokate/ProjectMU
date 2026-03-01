// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_SendGameplayEffect.generated.h"

class UMUAbilityTriggerPayload;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FGameplayEventSendData
{
	GENERATED_BODY()

public :
	FGameplayEventSendData()
	{
		TriggerPayloads.SetNum(2);
	}

	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag TargetToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UMUAbilityTriggerPayload*> TriggerPayloads;
	
};

UCLASS(DisplayName = "이벤트 전송")
class MOONU_API UAnimNotifyState_SendGameplayEffect : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	void SendGameplayEvent(USkeletalMeshComponent* MeshComp, const FGameplayEventSendData& NotifyData);

	
public :
	UPROPERTY(EditAnywhere)
	FGameplayEventSendData TriggerGameplayData;

	UPROPERTY(EditAnywhere)
	FGameplayEventSendData EndTriggerGameplayData;
};
