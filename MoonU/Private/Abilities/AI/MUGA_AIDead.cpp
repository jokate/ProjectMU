// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_AIDead.h"

#include "Abilities/AT/MUAT_CheckGoldenTime.h"
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

	UMUAT_CheckGoldenTime* NewTask = UMUAT_CheckGoldenTime::CreateNewTask(this, GoldenTimeInterval);
	NewTask->GoldenTimeSatisfied.AddDynamic(this, &UMUGA_AIDead::OnGoldenTimeFinished);
	NewTask->ReadyForActivation();
}

void UMUGA_AIDead::OnGoldenTimeFinished()
{
	AActor* TargetActor = CurrentActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		TargetActor->Destroy();
	}
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);	
}
