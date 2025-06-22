// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StageManagingComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageStarted, FName, StageName );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnStageCleared, FName, StageName );

UCLASS()
class MOONU_API UStageManagingComponent : public UActorComponent
{
	GENERATED_BODY()
public :

	virtual void BeginPlay() override;

	virtual void RegisterActor( AActor* NeedToRegActor );

	void CheckSpawn();
	// 등록하는 부분이 필요한 건 사실임.
	
	virtual void StartStage( FName StageName );

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

	//임의적인 설정값.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float SpawnDistance = 1000.f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float DestroyDistance = 2000.f;

	// 매 틱마다 체크하는 건 그럴 수 있음.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float SpawnTimeInterval = 0.5f;

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TArray<FName> StagePools;
	
	FTimerHandle SpawnCheckTimer;
};
