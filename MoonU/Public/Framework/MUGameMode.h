// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Interface/StageManager.h"
#include "Interface/TimeStopper.h"
#include "Interface/TimeWinder.h"
#include "MUGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API AMUGameMode : public AGameMode, public ITimeWinder, public ITimeStopper, public IStageManager
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

#pragma region IStageManager
	
	virtual void RegisterOwnerActor( AActor* LocalPlayer ) override;

#pragma endregion IStageManager

protected :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeWindManager> TimeWindManager;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeStopManager> TimeStopManager;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UStageManagingComponent> StageManagingComponent;
	
	UFUNCTION(Exec)
	virtual void CheatSetupEnforcement(int32 EnforcementID);

	UFUNCTION(Exec)
	virtual void CheatLevelUp();
};

