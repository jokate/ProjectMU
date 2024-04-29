// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_SetFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMUGA_SetFocus::UMUGA_SetFocus()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bRetriggerInstancedAbility = true;
}

void UMUGA_SetFocus::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	SetFocus();
}

void UMUGA_SetFocus::SetFocus()
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

	if (bSetFocus)
	{
		UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

		if (BBComponent)
		{
			AActor* TargetActor = Cast<AActor>(BBComponent->GetValueAsObject(TargetActorKey));

			if (TargetActor)
			{
				AIController->SetFocus(TargetActor);
			}
		}
	}
	else
	{
		AIController->ClearFocus(EAIFocusPriority::Gameplay);
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
