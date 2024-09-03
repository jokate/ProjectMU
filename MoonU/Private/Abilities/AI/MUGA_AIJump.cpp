// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_AIJump.h"

#include "Abilities/AT/MUAT_LaunchCharacter.h"
#include "Utility/VectorWrapper.h"

UMUGA_AIJump::UMUGA_AIJump()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AIJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const UVectorWrapper* VectorWrapper = Cast<UVectorWrapper>(TriggerEventData->OptionalObject);
	
	UMUAT_LaunchCharacter* Task = UMUAT_LaunchCharacter::CreateTask(this, VectorWrapper->GetVector());

	Task->OnLaunchCompleted.AddDynamic(this, &UMUGA_AIJump::OnLaunchEnded);

	Task->ReadyForActivation();
}

void UMUGA_AIJump::OnLaunchEnded()
{
	bool bEndAbility = true;
	bool bCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bEndAbility, bCancelled);
}
