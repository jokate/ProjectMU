﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_GoldenTime.h"

#include "Abilities/AT/MUAT_CheckGoldenTime.h"

void UMUGA_GoldenTime::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_CheckGoldenTime* GoldenTimeTask = UMUAT_CheckGoldenTime::CreateNewTask(this, GoldenTime);

	GoldenTimeTask->GoldenTimeSatisFied.AddDynamic(this, &UMUGA_GoldenTime::UMUGA_GoldenTime::OnGoldenTimeFinished);

	GoldenTimeTask->ReadyForActivation();
}

void UMUGA_GoldenTime::OnGoldenTimeFinished()
{
	UE_LOG(LogTemp, Log, TEXT("GOLDEN TIME"));
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
