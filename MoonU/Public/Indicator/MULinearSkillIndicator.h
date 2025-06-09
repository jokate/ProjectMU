// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUSkillIndicator.h"
#include "MULinearSkillIndicator.generated.h"

UCLASS()
class MOONU_API AMULinearSkillIndicator : public AMUSkillIndicator
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMULinearSkillIndicator();

protected:
	virtual void CalculateIndicatorMesh() override;

	virtual void SetupIndicatorInfo(APlayerController* OwnerController, float AttackDistance = 0, float InAOERadius = 0) override;

public:
	UPROPERTY( EditDefaultsOnly, Category = "Indicator Mesh" )
	TObjectPtr<UStaticMeshComponent> IndicatorMeshComponent;
};
