// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MUDefines.h"
#include "Abilities/MUAbilitySystemComponent.h"

bool UMUGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                            const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	if ( IsValid(ASC) )
	{
		bool bRes = true;
		if ( ActiveConditionCheck & static_cast<uint8>(EMUAbilityActiveType::SkillReady))
		{
			bRes &= !ASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_READYSKILL);
		}

		if ( ActiveConditionCheck & static_cast<uint8>(EMUAbilityActiveType::SkillCasting))
		{
			bRes &= !ASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_CASTINGSKILL);
		}

		if (bRes == false )
		{
			return false;
		}
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
