// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUSkillIndicator.h"
#include "MUCircularSkillIndicator.generated.h"

UCLASS()
class MOONU_API AMUCircularSkillIndicator : public AMUSkillIndicator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUCircularSkillIndicator();

protected:

	virtual void CalculateIndicatorMesh() override;

public:
	UPROPERTY( EditDefaultsOnly )
	TObjectPtr<UStaticMeshComponent> AOEMeshComponent;

	UPROPERTY( EditDefaultsOnly )
	TObjectPtr<UStaticMeshComponent> RadiusComponent;
};
