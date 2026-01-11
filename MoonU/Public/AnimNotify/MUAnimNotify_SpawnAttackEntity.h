// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "MUAnimNotify_SpawnAttackEntity.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUAnimNotify_SpawnAttackEntity : public UAnimNotify
{
	GENERATED_BODY()

public :
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bUseFixedPos = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", DisplayName = "고정 위치 오프셋.")
	FTransform FixedOffSet;
};
