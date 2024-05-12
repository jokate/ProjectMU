﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_AIDead.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"
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
	//파괴 전에 데이터를 기반으로 해서 아이템을 전달하는 방식으로 구현화를 이끌어야 한다.
	//내부 데이터를 기준으로 해서 아이템 풀을 기준으로 데이터를 반환하면 될 것으로 보임.

	FGameplayAbilityTargetData* EventData = CurrentEventData.TargetData.Get(0);

	TArray<TWeakObjectPtr<AActor>> InstigatorActorArr = EventData->GetActors();

	if (InstigatorActorArr.IsValidIndex(0))
	{
		AActor* InstigatorActor = InstigatorActorArr[0].Get();

		if (InstigatorActor->IsValidLowLevel())
		{
			// 해당 부분에서 아이템을 받아야 함.
			FGameplayEventData TargetEventData;
			TargetEventData.Instigator = GetOwningActorFromActorInfo();

			//임시적 코드 -> 이벤트 송신.
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InstigatorActor, MU_EVENT_BLOCKRECOVER, TargetEventData);
		}
	}
	
	AActor* TargetActor = CurrentActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		TargetActor->Destroy();
	}
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);	
}
