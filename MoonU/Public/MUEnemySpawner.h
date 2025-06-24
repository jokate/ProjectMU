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
	// 모드 상에서 관리될 명목하의 ID ( 해당 부분은, 다르게 설정해야 합니다. )
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FName SpawnerID = NAME_None;

	// 실제 스폰
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FName ReferenceID = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> NeedToSpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetActorLevel = 0 ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor> SpawnedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnCheckTimerInterval = 1.0f;

	UPROPERTY()
	TObjectPtr<class UTimeStopComponent> TimeStopComponent;
};