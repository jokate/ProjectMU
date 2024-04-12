// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeWindManager.h"

#include "Interface/TimerWindTarget.h"


// Sets default values for this component's properties
UTimeWindManager::UTimeWindManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTimeWindManager::BeginPlay()
{
	Super::BeginPlay();
}

void UTimeWindManager::TimeWindActivate()
{
	for (auto& RegisteredActor : RegisteredActors)
	{
		AActor* RegActor = RegisteredActor.Get();

		if (RegActor == nullptr)
		{
			continue;
		}

		if (ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(RegActor))
		{
			TimeWindTarget->SetTimeWind(true);
		}
	}
}

void UTimeWindManager::TimeWindDeactivate()
{
	for (auto& RegisteredActor : RegisteredActors)
	{
		AActor* RegActor = RegisteredActor.Get();

		if (RegActor == nullptr)
		{
			continue;
		}

		if (ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(RegActor))
		{
			TimeWindTarget->SetTimeWind(false);
		}
	}
}

void UTimeWindManager::RegisterTimeWindTarget(AActor* InActor)
{
	if (RegisteredActors.Contains(InActor))
	{
		return;
	}

	RegisteredActors.Add(InActor);
}

void UTimeWindManager::UnregisterTimeWindTarget(AActor* InActor)
{
	if (RegisteredActors.Contains(InActor))
	{
		RegisteredActors.Remove(InActor);
	}
}

