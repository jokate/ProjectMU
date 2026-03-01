// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "UObject/Object.h"
#include "MUAbilityTriggerPayload.generated.h"

struct FGameplayEventData;
/**
 * Baseline for AbilitySending Info (Sample, Data ID Or Spawn Class. etc...)
 */
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew )
class MOONU_API UMUAbilityTriggerPayload : public UObject
{
	GENERATED_BODY()
	
};


UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class MOONU_API UMUAbilityTriggerPayload_Trace : public UMUAbilityTriggerPayload
{
	GENERATED_BODY()

public :
	static const UMUAbilityTriggerPayload_Trace* GetTracePayload(const FGameplayEventData* EventData);
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FName DamageInfoName;
};