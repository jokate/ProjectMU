// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Interface/StageManager.h"
#include "Interface/TimeStopper.h"
#include "Interface/TimeWinder.h"
#include "MUGameMode.generated.h"

class UMUEnforcementManageComponent;
/**
 * 
 */
UCLASS()
class MOONU_API AMUGameMode : public AGameMode, public ITimeWinder, public ITimeStopper, public IStageManager
{
	GENERATED_BODY()

public :
	AMUGameMode();

	UMUEnforcementManageComponent* GetEnforcementManager() { return EnforcementManageComponent; }
protected :

#pragma region ITimeWinder
	virtual void TimeWindActivate() override;

	virtual void TimeWindDeactivate() override;
	
	virtual void RegisterTimeWindTarget(AActor* InActor) override;

	virtual void UnregisterTimeWindTarget(AActor* InActor) override;
#pragma endregion ITimeWinder

#pragma region ITimeStopper
	virtual void TimeStopActivate() override;

	virtual void TimeStopDeactivate() override;

	virtual void RegisterTimerStopTarget(AActor* InActor) override;

	virtual void UnregisterTimeStopTarget(AActor* InActor) override;
#pragma endregion ITimeStopper

#pragma region IStageManager
	
	virtual void RegisterOwnerActor( AActor* LocalPlayer ) override;
	
	virtual void SendClearSpawner( FName ClearedSpawnID ) override;

	virtual bool IsSpawnerCleared( FName SpawnerID ) override;

	virtual bool IsStageCleared( FName StageID ) override;

	virtual bool IsStageActiveOrCleared(FName StageID) override;

	virtual void RegisterStageSpawner( FName SpawnerID ) override;

	virtual void UnregisterStageSpawner( FName SpawnerID ) override;

	virtual FOnStageEvents& GetStageEvents() override;
	
	virtual void StartStage( FName StageID ) override;

#pragma endregion IStageManager

protected :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeWindManager> TimeWindManager;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeStopManager> TimeStopManager;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStageManagingComponent> StageManagingComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UMUEnforcementManageComponent> EnforcementManageComponent;
	
	UFUNCTION(Exec)
	virtual void CheatSetupEnforcement(int32 EnforcementID);

	UFUNCTION(Exec)
	virtual void CheatLevelUp();
};

