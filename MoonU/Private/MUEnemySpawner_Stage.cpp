// Fill out your copyright notice in the Description page of Project Settings.


#include "MUEnemySpawner_Stage.h"

#include "GameFramework/GameModeBase.h"
#include "Interface/StageManager.h"


// Sets default values
AMUEnemySpawner_Stage::AMUEnemySpawner_Stage()
{
}

// Called when the game starts or when spawned
void AMUEnemySpawner_Stage::BeginPlay()
{
	Super::BeginPlay();

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
	
	if ( StageManager->IsStageCleared( StageName ) == false )
	{
		FOnStageEvents& StageEvents = StageManager->GetStageEvents();
		StageEvents.OnStageStarted.AddDynamic( this, &AMUEnemySpawner_Stage::CompareAndSpawnEnemy);	
	}
}

void AMUEnemySpawner_Stage::EndPlay(const EEndPlayReason::Type EndPlayReason)
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
	
	if ( StageManager->IsStageCleared( StageName ) == false )
	{
		FOnStageEvents& StageEvents = StageManager->GetStageEvents();
		StageEvents.OnStageStarted.RemoveAll( this );	
	}
	
	Super::EndPlay(EndPlayReason);
}

void AMUEnemySpawner_Stage::CheckSpawn()
{
	Super::CheckSpawn();

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

	StageManager->RegisterStageSpawner( SpawnerID );
}

void AMUEnemySpawner_Stage::OnAllMonsterDeath()
{
	Super::OnAllMonsterDeath();

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

	StageManager->UnregisterStageSpawner( SpawnerID );
}

void AMUEnemySpawner_Stage::CompareAndSpawnEnemy(FName InStageName)
{
	SpawnEnemy();
}
