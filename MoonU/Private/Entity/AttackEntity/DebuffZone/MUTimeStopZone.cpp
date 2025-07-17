// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/DebuffZone/MUTimeStopZone.h"

#include "Interface/TimeStopper.h"


// Sets default values
AMUTimeStopZone::AMUTimeStopZone()
{
}

void AMUTimeStopZone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for ( TWeakObjectPtr<AActor>& TargetActor : ReactedActors )
	{
		AActor* ReactedActor = TargetActor.Get();

		if ( IsValid(ReactedActor) == false )
		{
			continue;
		}
		
		ITimeStopper* TimeStop = Cast<ITimeStopper>(ReactedActor);

		if ( TimeStop != nullptr )
		{
			TimeStop->TimeStopDeactivate();
		}
	}
	Super::EndPlay(EndPlayReason);
}

void AMUTimeStopZone::OnReacted(AActor* ReactedActor)
{
	Super::OnReacted(ReactedActor);

	ITimeStopper* TimeStop = Cast<ITimeStopper>(ReactedActor);

	if ( TimeStop != nullptr )
	{
		TimeStop->TimeStopActivate();
	}
}
