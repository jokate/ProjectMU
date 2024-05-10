// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUGameMode.h"

#include "Components/TimeStopManager.h"
#include "Components/TimeWindManager.h"

AMUGameMode::AMUGameMode()
{
	TimeWindManager = CreateDefaultSubobject<UTimeWindManager>("TimeWindManager");
	TimeStopManager = CreateDefaultSubobject<UTimeStopManager>("TimeStopManager");
}

void AMUGameMode::TimeWindActivate()
{
	TimeWindManager->TimeWindActivate();
}

void AMUGameMode::TimeWindDeactivate()
{
	TimeWindManager->TimeWindDeactivate();
}

void AMUGameMode::RegisterTimeWindTarget(AActor* InActor)
{
	TimeWindManager->RegisterTimeWindTarget(InActor);
}

void AMUGameMode::UnregisterTimeWindTarget(AActor* InActor)
{
	TimeWindManager->UnregisterTimeWindTarget(InActor);
}

void AMUGameMode::TimeStopActivate()
{
	TimeStopManager->TimeStopActivate();
}

void AMUGameMode::TimeStopDeactivate()
{
	TimeStopManager->TimeStopDeactivate();
}

void AMUGameMode::RegisterTimerStopTarget(AActor* InActor)
{
	TimeStopManager->RegisterTimerStopTarget(InActor);
}

void AMUGameMode::UnregisterTimeStopTarget(AActor* InActor)
{
	TimeStopManager->UnregisterTimeStopTarget(InActor);
}
