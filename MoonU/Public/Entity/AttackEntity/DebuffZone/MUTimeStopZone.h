// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/AttackEntity/MUCircularZone.h"
#include "MUTimeStopZone.generated.h"

UCLASS()
class MOONU_API AMUTimeStopZone : public AMUCircularZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUTimeStopZone();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void OnReacted(AActor* ReactedActor) override;
};
