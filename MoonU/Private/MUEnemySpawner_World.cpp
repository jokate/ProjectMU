// Fill out your copyright notice in the Description page of Project Settings.


#include "MUEnemySpawner_World.h"

#include "GameFramework/GameModeBase.h"
#include "Interface/StageManager.h"

// Sets default values
AMUEnemySpawner_World::AMUEnemySpawner_World()
{
}

// Called when the game starts or when spawned
void AMUEnemySpawner_World::BeginPlay()
{
	Super::BeginPlay();
	
	CheckSpawn();
}

void AMUEnemySpawner_World::OnAllMonsterDeath()
{
	Super::OnAllMonsterDeath();
	
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

	StageManager->SendClearSpawner( SpawnerID );
}

