// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeStopManager.h"


// Sets default values for this component's properties
UTimeStopManager::UTimeStopManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTimeStopManager::BeginPlay()
{
	Super::BeginPlay();
}

void UTimeStopManager::RegisterTimerStopTarget(AActor* InActor)
{
	if (RegActors.Contains(InActor))
	{
		return;
	}

	RegActors.Add(InActor);
}

void UTimeStopManager::UnregisterTimeStopTarget(AActor* InActor)
{
	if (!RegActors.Contains(InActor))
	{
		return;
	}

	RegActors.Remove(InActor);
}

void UTimeStopManager::TimeStopActivate()
{
}

void UTimeStopManager::TimeStopDeactivate()
{
}




