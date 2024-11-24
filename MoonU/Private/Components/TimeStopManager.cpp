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

	//현재 시간이 멈춘 경우에는 스포너에서 지속 스폰되더라도 멈추도록 설계
	if (bIsTimeStopped)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InActor, MU_EVENT_TIMESTOP, FGameplayEventData());
	}
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
	bIsTimeStopped = true;
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
	bIsTimeStopped = false;
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




