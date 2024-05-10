// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeStopManager.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"


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
	for (auto& RegisteredActor : RegActors)
	{
		AActor* RegActor = RegisteredActor.Get();

		if (RegActor == nullptr)
		{
			continue;
		}
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(RegActor, MU_EVENT_TIMESTOP, FGameplayEventData());
	}
}

void UTimeStopManager::TimeStopDeactivate()
{
	for (auto& RegisteredActor : RegActors)
	{
		AActor* RegActor = RegisteredActor.Get();

		if (RegActor == nullptr)
		{
			continue;
		}
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(RegActor, MU_EVENT_TIMESTOPEND, FGameplayEventData());
	}
}




