// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUEnemySpawner.h"
#include "MUEnemySpawner_Stage.generated.h"

UCLASS()
class MOONU_API AMUEnemySpawner_Stage : public AMUEnemySpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUEnemySpawner_Stage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void CheckSpawn() override;

	virtual void OnAllMonsterDeath() override;

	UFUNCTION()
	virtual void CompareAndSpawnEnemy( FName InStageName );

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FName StageName = NAME_None;
};
