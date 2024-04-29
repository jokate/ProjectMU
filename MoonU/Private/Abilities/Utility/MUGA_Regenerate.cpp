// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_Regenerate.h"

#include "AI/MUAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMUGA_Regenerate::UMUGA_Regenerate()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_Regenerate::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	RegenerateOperation();
}

void UMUGA_Regenerate::RegenerateOperation()
{
	ACharacter* TargetCharacter = CastChecked<ACharacter>(CurrentActorInfo->AvatarActor.Get());
	if (TargetCharacter == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	AMUAIController* AIController = CastChecked<AMUAIController>(UAIBlueprintHelperLibrary::GetAIController(TargetCharacter));

	if (AIController == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
	
	TargetCharacter->SetActorEnableCollision(true);
	
	auto* CharacterMovement = TargetCharacter->GetCharacterMovement();

	if (CharacterMovement == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	CharacterMovement->SetDefaultMovementMode();
	
	AIController->RunAI();
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
