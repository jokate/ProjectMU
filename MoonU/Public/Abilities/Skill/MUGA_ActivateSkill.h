﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/SkillActivateAbility.h"
#include "MUGA_ActivateSkill.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSkillStateChanged );

UCLASS()
class MOONU_API UMUGA_ActivateSkill : public UGameplayAbility, public ISkillActivateAbility
{
	GENERATED_BODY()

public :
	
	UMUGA_ActivateSkill();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual bool CanUseSkill();

	virtual void CastSkill();
	
	virtual void ActivateSkill() override;

	virtual void CancelSkill() override;

	virtual void SkillTriggered( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo );

	virtual void SkillUnTriggered( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo );
	
public :
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer GameplayCueTags;

	UPROPERTY( BlueprintAssignable )
	FOnSkillStateChanged OnSkillStateChanged;
	
	UPROPERTY( EditDefaultsOnly )
	FName SkillID = NAME_None;
};
