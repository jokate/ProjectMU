// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_PlayerDead.h"

#include "GameFramework/Character.h"

void UMUGA_PlayerDead::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* TargetCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get());

	if (TargetCharacter)
	{
		APlayerController* PC = CastChecked<APlayerController>(TargetCharacter->GetController());

		if (PC)
		{
			TargetCharacter->DisableInput(PC);
		}
	}
}
