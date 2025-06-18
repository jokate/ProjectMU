// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Interface/TimeStopper.h"
#include "Interface/TimeWinder.h"
#include "MUGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API AMUGameMode : public AGameMode, public ITimeWinder, public ITimeStopper
{
	GENERATED_BODY()

public :
	AMUGameMode();

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

#pragma region IWorldManager
	// 월드 관련한 부분에 대해서 로드 언로드 하는 부분에 대해서 관리하는 거가 필요함.
	// Register 되고 관리가 되어야 하나?
	// 로컬 플레이 기준으로 하면..
#pragma endregion IWorldManager
protected :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeWindManager> TimeWindManager;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeStopManager> TimeStopManager;
	
	UFUNCTION(Exec)
	virtual void CheatSetupEnforcement(int32 EnforcementID);

	UFUNCTION(Exec)
	virtual void CheatLevelUp();
};

