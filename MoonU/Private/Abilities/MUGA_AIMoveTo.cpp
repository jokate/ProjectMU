// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_AIMoveTo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/AT/MUAT_MoveToAI.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UMUGA_AIMoveTo::UMUGA_AIMoveTo()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_AIMoveTo::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	MoveToAITask = UMUAT_MoveToAI::CreateTask(this, TargetKeyName, BlackboardKeyData, AcceptanceRadius);

	MoveToAITask->MoveCompleted.AddDynamic(this, &UMUGA_AIMoveTo::OnCompleteMove);
	
	MoveToAITask->ReadyForActivation();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurrentActorInfo->AvatarActor.Get());

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.FindOrAdd(RetriggerTag).AddUObject(this, &UMUGA_AIMoveTo::OnRetriggered);
	}
}

void UMUGA_AIMoveTo::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(CurrentActorInfo->AvatarActor.Get());

	if (ASC)
	{
		ASC->GenericGameplayEventCallbacks.Remove(RetriggerTag);
	}
	
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_AIMoveTo::OnCompleteMove(const FAIRequestID RequestID, EPathFollowingResult::Type InType)
{
	AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();

	if (AvatarActor == nullptr)
	{
		return;
	}
	
	bool bEndAbility = true;
	bool bCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bEndAbility, bCancelled);
}

void UMUGA_AIMoveTo::OnRetriggered(const FGameplayEventData* EventData)
{
	if (MoveToAITask)
	{
		MoveToAITask->AIMove();
	}
}
