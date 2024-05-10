// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeStopComponent.h"

#include "Interface/TimeStopper.h"


// Sets default values for this component's properties
UTimeStopComponent::UTimeStopComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTimeStopComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnInitialized();
}

void UTimeStopComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnEndPlay();
	Super::EndPlay(EndPlayReason);
}

void UTimeStopComponent::OnInitialized()
{
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (GM == nullptr)
	{
		return;
	}

	ITimeStopper* TimeStopper = Cast<ITimeStopper>(GM);

	if (TimeStopper == nullptr)
	{
		return;
	}

	TimeStopper->RegisterTimerStopTarget(GetOwner());
}

void UTimeStopComponent::OnEndPlay()
{
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (GM == nullptr)
	{
		return;
	}

	ITimeStopper* TimeStopper = Cast<ITimeStopper>(GM);

	if (TimeStopper == nullptr)
	{
		return;
	}

	TimeStopper->UnregisterTimeStopTarget(GetOwner());
}


	