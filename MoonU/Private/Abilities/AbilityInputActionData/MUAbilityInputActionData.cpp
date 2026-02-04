// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityInputActionData/MUAbilityInputActionData.h"

#include "MUDefines.h"
#include "Abilities/Skill/MUGA_ActivateSkill.h"

bool FAbilityInputActionBase::IsSatisfiedInput(const FGameplayTag& SkillInputTag)
{
	if ( InputTagContainer.IsEmpty() == true )
	{
		return false;
	}
	
	return InputTagContainer.HasTagExact(SkillInputTag);
}

bool FAbilityInputAction_SetComboPressed::OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_FALSE_IF_INVALID(SkillAbility);
	
	SkillAbility->SetComboPressed();
	return true;
}

bool FAbilityInputAction_PlayMontage::OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_FALSE_IF_INVALID(SkillAbility);
	
	SkillAbility->SetupAnimMontage(TargetToPlayMontage);
	return true;
}

bool FAbilityInputAction_TriggerAbility::OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_FALSE_IF_INVALID(SkillAbility);
	
	SkillAbility->TriggerAbility(AbilityClass);
	return true;
}

bool FAbilityInputAction_EndAbility::OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_FALSE_IF_INVALID(SkillAbility);
	
	SkillAbility->CancelAbility_External();
	return true;
}

bool FAbilityInputAction_CastSkill::OnInputEventCallback(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_FALSE_IF_INVALID(SkillAbility);
	
	SkillAbility->CastSkill();
	return true;
}
