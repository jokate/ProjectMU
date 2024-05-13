// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_TraceForInteraction.h"

#include "Abilities/AT/MUAT_TraceforInteraction.h"
#include "Interface/Interactor.h"

UMUGA_TraceForInteraction::UMUGA_TraceForInteraction()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_TraceForInteraction::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_TraceforInteraction* NewTask = UMUAT_TraceforInteraction::CreateTask(this, InteractionRadius, LineCastLength);

	NewTask->InteractionCheckFinished.AddDynamic(this, &UMUGA_TraceForInteraction::SetTargetActor);
	NewTask->ReadyForActivation();
}

void UMUGA_TraceForInteraction::SetTargetActor(AActor* TargetActor)
{
	AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();

	if (AvatarActor == nullptr)
	{
		return;
	}

	IInteractor* Interactor = Cast<IInteractor>(AvatarActor);

	if (Interactor == nullptr)
	{
		return;
	}

	Interactor->SetCachedInteractionTarget(TargetActor);
}



