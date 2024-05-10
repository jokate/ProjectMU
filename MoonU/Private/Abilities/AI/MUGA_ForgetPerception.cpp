// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_ForgetPerception.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

void UMUGA_ForgetPerception::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ForgetPerception();
}

void UMUGA_ForgetPerception::ForgetPerception()
{
	APawn* TargetPawn = Cast<APawn>(CurrentActorInfo->AvatarActor.Get());

	if (TargetPawn == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	AAIController* AIController = Cast<AAIController>(TargetPawn->GetController());

	if (AIController == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	UAIPerceptionComponent* PCM = AIController->PerceptionComponent;

	if (PCM == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	} 

	PCM->ForgetAll();
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
