// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

#include "MUDefines.h"
#include "Data/MUStruct.h"
#include "Interface/SkillInputTarget.h"

UMUGA_IndicatorSkill::UMUGA_IndicatorSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	ActivationOwnedTags.AddTag(MU_CHARACTERSTATE_READYSKILL);
}

void UMUGA_IndicatorSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const FGameplayEventData_Skill* EventData = static_cast<const FGameplayEventData_Skill*>(TriggerEventData);

	if ( EventData == nullptr )
	{
		return;
	}

	AActor* AvatarActor = ActorInfo->AvatarActor.Get();

	if ( ISkillInputTarget* SkillInputTarget = Cast<ISkillInputTarget>(AvatarActor) )
	{
		FOnSkillActivate& SkillActivateEvent = SkillInputTarget->GetActivationSkillEvent();
		SkillActivateEvent.AddUObject( this, &UMUGA_IndicatorSkill::ActivateSkill );

		FOnSkillDeactivate& DeactivateEvent = SkillInputTarget->GetDeactivationSkillEvent();
		DeactivateEvent.AddUObject( this, &UMUGA_IndicatorSkill::CancelSkill );
	}
}

void UMUGA_IndicatorSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();

	if ( ISkillInputTarget* SkillInputTarget = Cast<ISkillInputTarget>(AvatarActor) )
	{
		FOnSkillActivate& SkillActivateEvent = SkillInputTarget->GetActivationSkillEvent();
		SkillActivateEvent.RemoveAll( this );

		FOnSkillDeactivate& DeactivateEvent = SkillInputTarget->GetDeactivationSkillEvent();
		DeactivateEvent.RemoveAll( this );
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_IndicatorSkill::ActivateSkill()
{
	// 스킬 캐스팅에 대한 부분 처리.
	
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_IndicatorSkill::CancelSkill()
{
	// 스킬 취소 캐스팅

	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
