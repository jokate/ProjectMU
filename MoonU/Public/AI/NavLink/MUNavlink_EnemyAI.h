// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "MUNavlink_EnemyAI.generated.h"

UCLASS()
class MOONU_API AMUNavlink_EnemyAI : public ANavLinkProxy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUNavlink_EnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	virtual void OnAIReachedToPoint(AActor* MovingActor, const FVector& DestinationPoint);
};
