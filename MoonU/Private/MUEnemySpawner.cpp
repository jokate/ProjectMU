// Fill out your copyright notice in the Description page of Project Settings.


#include "MUEnemySpawner.h"

#include "Character/MUCharacterNonPlayer.h"
#include "Components/TimeStopComponent.h"
#include "GameFramework/GameMode.h"
#include "Interface/LevelManager.h"
#include "Interface/StageManager.h"
#include "Library/MUFunctionLibrary.h"

AMUEnemySpawner::AMUEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	TimeStopComponent = CreateDefaultSubobject<UTimeStopComponent>(TEXT("TimeStopComponent"));
}

// 관련 부분 재정비 필요.
void AMUEnemySpawner::CheckSpawn()
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
	FMUMonsterSpawnList SpawnerData;
	if ( UMUFunctionLibrary::GetMonsterData( this, ReferenceID, SpawnerData ) == false )
	{
		return;
	}

	for ( FMUMonsterSpawnData& Spawner : SpawnerData.SpawnDatas )
	{
		for ( int32 i = 0; i < Spawner.SpawnCount; i++ )
		{
			float RandomPositionOffset = FMath::RandRange(0.f, SpawnRadius);
			FVector SpawnLocation = GetActorLocation() + FVector::OneVector * RandomPositionOffset;

			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);
	
			AMUCharacterNonPlayer* DeferredActor = GetWorld()->SpawnActorDeferred<AMUCharacterNonPlayer>(Spawner.CharacterClass, SpawnTransform, this, nullptr);

			if (IsValid(DeferredActor) == false )
			{
				continue;
			}
	
			ILevelManager* LevelManager = Cast<ILevelManager>(DeferredActor);

			if (LevelManager == nullptr)
			{
				continue;
			}
			
			
			DeferredActor->SpawnDefaultController();
			LevelManager->SetLevel(TargetActorLevel);
			DeferredActor->FinishSpawning(SpawnTransform);
			DeferredActor->EnemyDeath.AddDynamic( this, &AMUEnemySpawner::OnMonsterDeath );
			DeferredActor->SetCharacterID(Spawner.CharacterID);
			
			SpawnedActor.Add( DeferredActor );
		}
	}
}

void AMUEnemySpawner::OnMonsterDeath(AActor* DeadActor)
{
	SpawnedActor.Remove( DeadActor );

	if ( SpawnedActor.IsEmpty() == true )
	{
		OnAllMonsterDeath();
	}
}

void AMUEnemySpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for ( AActor* SpawnActor : SpawnedActor )
	{
		SpawnActor->Destroy();
	}

	SpawnedActor.Empty();
	
	Super::EndPlay(EndPlayReason);
}
