// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/DebuffZone/MUTimeStopZone.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"


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
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ReactedActor, MU_EVENT_TIMESTOPEND, FGameplayEventData());
	}
	Super::EndPlay(EndPlayReason);
}

void AMUTimeStopZone::OnReacted(AActor* ReactedActor)
{
	Super::OnReacted(ReactedActor);
	
	if (IsValid(ReactedActor) == false )
	{
		return;
	}
		
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ReactedActor, MU_EVENT_TIMESTOP, FGameplayEventData());
}
