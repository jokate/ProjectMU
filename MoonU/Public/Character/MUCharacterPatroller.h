// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUCharacterNonPlayer.h"
#include "Interface/Patroller.h"
#include "MUCharacterPatroller.generated.h"

UCLASS()
class MOONU_API AMUCharacterPatroller : public AMUCharacterNonPlayer, public IPatroller
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMUCharacterPatroller();

#pragma region IPatroller
	virtual void IncrementPatrolRoute() override;

	UFUNCTION(BlueprintCallable)
	virtual const FVector GetPositionForSpline() override;
#pragma endregion
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TObjectPtr<class USplineComponent> SplineComponent;

	UPROPERTY(VisibleAnywhere, BLueprintReadWrite, Category = "Patrol")
	int32 PatrolIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Patrol")
	int32 PatrolDirection;
};
