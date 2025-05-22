// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MUSkillIndicator.generated.h"

UCLASS()
class MOONU_API AMUSkillIndicator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUSkillIndicator();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void CalculateIndicatorMesh();

	virtual void SetupIndicatorInfo( APlayerController* OwnerController, float AttackDistance = 0, float InAOERadius = 0 );

	virtual FVector GetTargetLocation() { return FVector::ZeroVector; }

	virtual FRotator GetTargetRotation() { return FRotator::ZeroRotator; }

public :
	UPROPERTY()
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY( BlueprintReadOnly )
	float MaxAttackDistance;

	UPROPERTY( BlueprintReadOnly )
	float AOERadius;
};
