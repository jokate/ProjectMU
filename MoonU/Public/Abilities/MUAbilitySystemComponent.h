// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MUAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUAbilitySystemComponent();

public:
	
	virtual void AllocateSkill( FName SkillID, const FGameplayAbilitySpec& AbilitySpec );

	virtual void DeallocateSkill( FName SkillID );

	virtual FGameplayAbilitySpec* FindAbilitySpecBySkillID( FName SkillID );

	virtual void TryTriggerSkill( FName SkillID );

	virtual void TryCancelSkill( FName SkillID );

public :
	UPROPERTY()
	TMap<FName, FGameplayAbilitySpecHandle> SkillAbilitySpec;
	
};