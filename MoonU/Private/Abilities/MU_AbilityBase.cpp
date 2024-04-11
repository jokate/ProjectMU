// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MU_AbilityBase.h"

#include "Interface/TimerWindTarget.h"

bool UMU_AbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                         const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	const bool bCanActivateBase =  Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);

	if (!bCanActivateBase)
	{
		return false;
	}
	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(ActorInfo->AvatarActor.Get());

	if (!TimeWindTarget)
	{
		return bCanActivateBase;
	}

	return !TimeWindTarget->GetTimeWind();
}
