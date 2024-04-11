// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUGameMode.h"

#include "Components/TimeWindManager.h"

AMUGameMode::AMUGameMode()
{
	TimeWindManager = CreateDefaultSubobject<UTimeWindManager>("TimeWindManager");
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
