// Fill out your copyright notice in the Description page of Project Settings.


#include "MUEnemySpawner.h"

#include "Components/TimeStopComponent.h"
#include "GameFramework/Character.h"
#include "Interface/LevelManager.h"

AMUEnemySpawner::AMUEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	TimeStopComponent = CreateDefaultSubobject<UTimeStopComponent>(TEXT("TimeStopComponent"));
}

void AMUEnemySpawner::SpawnTimerCheckFunction()
{
	if (IsValid(SpawnedActor) == true )
	{
		UE_LOG(LogTemp, Log, TEXT("Already Spawned Actor"))
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

	SpawnedActor = DeferredActor;
}

void AMUEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMUEnemySpawner::SpawnTimerCheckFunction, SpawnCheckTimerInterval, true );
}
