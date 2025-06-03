// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/SkillActivateAbility.h"
#include "MUGA_ActivateSkill.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUGA_ActivateSkill : public UGameplayAbility, public ISkillActivateAbility
{
	GENERATED_BODY()

public :
	
	UMUGA_ActivateSkill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void ActivateSkill() override {}

	virtual void CancelSkill() override {};

	virtual void SkillTriggered( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo );

	virtual void SkillUnTriggered( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo );
	
public :
};
