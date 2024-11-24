// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MUEnemySpawner.generated.h"

UCLASS()
class MOONU_API AMUEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUEnemySpawner();

	virtual void SpawnTimerCheckFunction();
	
	virtual void SpawnEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
protected :
	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> NeedToSpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetActorLevel = 0 ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> SpawnedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnCheckTimerInterval = 1.0f;

	UPROPERTY()
	TObjectPtr<class UTimeStopComponent> TimeStopComponent;
};