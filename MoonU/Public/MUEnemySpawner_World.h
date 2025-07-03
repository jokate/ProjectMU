// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUEnemySpawner.h"
#include "MUEnemySpawner_World.generated.h"

UCLASS()
class MOONU_API AMUEnemySpawner_World : public AMUEnemySpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUEnemySpawner_World();
		
	virtual void OnAllMonsterDeath() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
