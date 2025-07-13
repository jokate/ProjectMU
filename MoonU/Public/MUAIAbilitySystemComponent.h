// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "MUAIAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUAIAbilitySystemComponent : public UMUAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUAIAbilitySystemComponent();

	virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) override;

	virtual bool  RetriggerAbility( FGameplayAbilitySpecHandle& AbilitySpec );
};
