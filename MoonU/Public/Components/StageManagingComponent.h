// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Interface/StageManager.h"
#include "StageManagingComponent.generated.h"

/**
 * 
 */
USTRUCT( BlueprintType )
struct FStagePoolingData
{
	GENERATED_BODY()

public :
	FStagePoolingData() {}

	FStagePoolingData(FName InStageName, FVector2D InVector) : StageName(InStageName), SpawnLocation(InVector) {}
	
public :
	UPROPERTY( BlueprintReadOnly )
	FName StageName = NAME_None;

	UPROPERTY( BlueprintReadOnly )
	FVector2D SpawnLocation = FVector2D::ZeroVector;

	bool operator==( const FName& InName ) const
	{
		return StageName == InName;
	}
};

UCLASS()
class MOONU_API UStageManagingComponent : public UActorComponent, public IStageManager
{
	GENERATED_BODY()
public :
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void RegisterOwnerActor( AActor* NeedToRegActor ) override;
	virtual void SendClearSpawner( FName ClearedSpawnID ) override;
	virtual FOnStageEvents& GetStageEvents() override { return StageEvents; }
	virtual bool IsStageCleared(FName StageID) override;
	
	virtual bool IsSpawnerCleared(FName SpawnerID) override { return ClearedMonsterSpawner.Contains(SpawnerID);}
	virtual void SetupStage();

	UFUNCTION()
	void CheckSpawn();
	
	// 등록하는 부분이 필요한 건 사실임.
	virtual void StartStage( FName InStageName ) override;

	virtual void EndStage();
	
	virtual void RegisterUnit( FName UnitName );

	virtual void UnregisterUnit( FName UnitName );

	virtual void RegisterStageSpawner( FName SpawnerID ) override { SpawnerNames.Add(SpawnerID); };

	virtual void UnregisterStageSpawner( FName SpawnerID ) override { SpawnerNames.Remove(SpawnerID); }

	bool CheckIsValidPosition( FVector2D RandPos );
public :

	UPROPERTY()
	FOnStageEvents StageEvents;

public :
	
	UPROPERTY( VisibleAnywhere )
	TMap<FName, int32> StageCount;

	UPROPERTY( VisibleAnywhere )
	FName CurrentStageName = NAME_None;

	UPROPERTY( VisibleAnywhere )
	TArray<FName> SpawnerNames;
	
	UPROPERTY( VisibleAnywhere )
	TSet<FName> ClearedStage;

#pragma region Spawners
	
	UPROPERTY( VisibleAnywhere )
	TSet<FName> ClearedMonsterSpawner;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float SpawnTimeInterval = 0.5f;
	
#pragma endregion

#pragma region StagePool
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName StageName = NAME_None;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FStagePoolingData> StagePools;

#pragma endregion 

	// 등록하는 것.
	UPROPERTY( VisibleAnywhere )
	AActor* OwnerActor;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float SpawnDistance = 12800.f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float DestroyDistance = 25600.f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float StageSpawnCheckDistance = 6400.f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float StageSpawnHeight = 10000.f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FVector2D WorldRand = FVector2D::ZeroVector;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, ULevelStreamingDynamic*> StreamedLevelList;
	
	FTimerHandle SpawnCheckTimer;
};