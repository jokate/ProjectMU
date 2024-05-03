﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_AIDead.h"

#include "AI/MUAIController.h"
#include "GameFramework/Character.h"

void UMUGA_AIDead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* TargetCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());

	if (TargetCharacter)
	{
		AMUAIController* AIController = CastChecked<AMUAIController>(TargetCharacter->GetController());

		if (AIController)
		{
			AIController->StopAI();

			AIController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
