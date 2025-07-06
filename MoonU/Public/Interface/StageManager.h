// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StageManager.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UStageManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageStarted, FName, StageName );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageCleared, FName, StageName );

USTRUCT()
struct FOnStageEvents
{
	GENERATED_BODY()

	UPROPERTY( BlueprintAssignable )
	FOnStageStarted OnStageStarted;

	UPROPERTY( BlueprintAssignable )
	FOnStageCleared OnStageCleared;
};

class MOONU_API IStageManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void RegisterOwnerActor( AActor* LocalPlayer ) = 0;

	virtual void SendClearSpawner( FName ClearedSpawnID ) = 0;

	virtual bool IsSpawnerCleared( FName SpawnerID ) = 0;

	virtual void StartStage( FName StageID ) = 0;

	virtual bool IsStageCleared( FName StageID ) = 0;

	virtual bool IsStageActiveOrCleared( FName StageID ) = 0;

	virtual void RegisterStageSpawner( FName SpawnerID ) = 0;

	virtual void UnregisterStageSpawner( FName SpawnerID ) = 0;

	virtual FOnStageEvents& GetStageEvents() = 0;
};
