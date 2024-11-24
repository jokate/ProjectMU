// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/TimeStopper.h"
#include "TimeStopManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UTimeStopManager : public UActorComponent, public ITimeStopper
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTimeStopManager();
	
#pragma region ITimeStopper

	virtual void RegisterTimerStopTarget(AActor* InActor) override;

	virtual void UnregisterTimeStopTarget(AActor* InActor) override;

	virtual void TimeStopActivate() override;
	
	virtual void TimeStopDeactivate() override;

#pragma endregion ITimeStopper
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
protected: 
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<AActor>> RegActors;

private:
	bool bIsTimeStopped = false;
};
