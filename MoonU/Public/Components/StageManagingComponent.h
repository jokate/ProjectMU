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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageStarted, FName, StageName );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageCleared, FName, StageName );

UCLASS()
class MOONU_API UStageManagingComponent : public UActorComponent, public IStageManager
{
	GENERATED_BODY()
public :
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void RegisterOwnerActor( AActor* NeedToRegActor ) override;
	virtual void SendClearSpawner( FName ClearedSpawnID ) override;
	virtual bool IsSpawnerCleared(FName SpawnerID) override { return ClearedMonsterSpawner.Contains(SpawnerID);}
	virtual void SetupStage();

	UFUNCTION()
	void CheckSpawn();
	
	// 등록하는 부분이 필요한 건 사실임.
	virtual void StartStage( FName InStageName );

	virtual void EndStage();
	
	virtual void RegisterUnit( FName UnitName );

	virtual void UnregisterUnit( FName UnitName );
	
public :

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnStageStarted OnStageStarted;

	UPROPERTY( BlueprintAssignable, BlueprintCallable )
	FOnStageCleared OnStageCleared;

public :
	
	UPROPERTY( VisibleAnywhere )
	TMap<FName, int32> StageCount;

	UPROPERTY( VisibleAnywhere )
	FName CurrentStageName = NAME_None;

	// 등록하는 것.
	UPROPERTY( VisibleAnywhere )
	AActor* OwnerActor;

	UPROPERTY( VisibleAnywhere )
	TSet<FName> ClearedMonsterSpawner;
	
	// 매 틱마다 체크하는 건 그럴 수 있음.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float SpawnTimeInterval = 0.5f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName StageName = NAME_None;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FName> StagePools;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float SpawnDistance = 12800.f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float DestroyDistance = 25600.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, ULevelStreamingDynamic*> StreamedLevelList;
	
	FTimerHandle SpawnCheckTimer;

	//FRandomStream SamplingSeed;
};
