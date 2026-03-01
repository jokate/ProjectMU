// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_SendGameplayEffect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/MUAbilityTriggerPayload.h"

void UAnimNotifyState_SendGameplayEffect::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	SendGameplayEvent(MeshComp, TriggerGameplayData);
}

void UAnimNotifyState_SendGameplayEffect::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	SendGameplayEvent(MeshComp, EndTriggerGameplayData);
}

void UAnimNotifyState_SendGameplayEffect::SendGameplayEvent(USkeletalMeshComponent* MeshComp,
	const FGameplayEventSendData& NotifyData)
{
	AActor* OwnerActor = MeshComp->GetOwner();

	if ( IsValid(OwnerActor) == false )
	{
		return;
	} 
	
	FGameplayEventData EventData;

	const TArray<UMUAbilityTriggerPayload*>& Payloads = NotifyData.TriggerPayloads;
	for ( int32 i = 0; i < 2; ++i )
	{
		if ( Payloads.IsValidIndex(i) == false )
		{
			continue;
		}

		i == 0 ? EventData.OptionalObject = Payloads[i] : EventData.OptionalObject2 = Payloads[i];
	}
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, NotifyData.TargetToTrigger, EventData);
}

