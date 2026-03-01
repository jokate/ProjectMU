// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUAbilityTriggerPayload.h"

const UMUAbilityTriggerPayload_Trace* UMUAbilityTriggerPayload_Trace::GetTracePayload(
	const FGameplayEventData* EventData)
{
	if ( EventData->OptionalObject == nullptr && EventData->OptionalObject2 == nullptr )
		return nullptr;
	
	const UMUAbilityTriggerPayload_Trace* TraceData = Cast<UMUAbilityTriggerPayload_Trace>(EventData->OptionalObject);

	return IsValid(TraceData) ? TraceData : Cast<UMUAbilityTriggerPayload_Trace>(EventData->OptionalObject2);
}
