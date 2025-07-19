// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_PlayerAirAttack.h"

#include "Abilities/AT/MUAT_SetNoSimulatedPhysics.h"


void UMUGA_PlayerAirAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_SetNoSimulatedPhysics* NewTask = UMUAT_SetNoSimulatedPhysics::CreateTask( this );

	if ( IsValid( NewTask ) == true )
	{
		NewTask->ReadyForActivation();
	}
}
