// Fill out your copyright notice in the Description page of Project Settings.


#include "MUEnemySpawner.h"

#include "Components/TimeStopComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameMode.h"
#include "Interface/LevelManager.h"
#include "Interface/StageManager.h"

AMUEnemySpawner::AMUEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	TimeStopComponent = CreateDefaultSubobject<UTimeStopComponent>(TEXT("TimeStopComponent"));
}

// 관련 부분 재정비 필요.
void AMUEnemySpawner::SpawnTimerCheckFunction()
{
	// 스테이징 매니징에서 클리어 판정 처리 필요.
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (IsValid(GM) == false)
	{
		return;
	}

	IStageManager* StageManager = Cast<IStageManager>(GM);

	if ( StageManager == nullptr )
	{
		return;
	}

	if ( StageManager->IsSpawnerCleared(SpawnerID) == true )
	{
		return;
	} 

	SpawnEnemy();
}

void AMUEnemySpawner::SpawnEnemy()
{
	if ( IsValid( GetWorld() ) == false )
	{
		return;
	}

	// 스포너 로직 재정비 필요.
	
 	/*
 	float RandomPositionOffset = FMath::RandRange(0.f, SpawnRadius);
	FVector SpawnLocation = GetActorLocation() + FVector::OneVector * RandomPositionOffset;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	
	ACharacter* DeferredActor = GetWorld()->SpawnActorDeferred<ACharacter>(NeedToSpawnActorClass, SpawnTransform, this, nullptr);

	if (IsValid(DeferredActor) == false )
	{
		return;
	}
	
	ILevelManager* LevelManager = Cast<ILevelManager>(DeferredActor);

	if (LevelManager == nullptr)
	{
		return;
	}
	DeferredActor->SpawnDefaultController();
	LevelManager->SetLevel(TargetActorLevel);
	DeferredActor->FinishSpawning(SpawnTransform);
	*/

	//SpawnedActor = DeferredActor;
}

// 시작시 아님.
void AMUEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	
}
