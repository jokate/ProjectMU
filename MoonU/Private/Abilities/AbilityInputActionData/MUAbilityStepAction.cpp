// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AbilityInputActionData/MUAbilityStepAction.h"

#include "MUDefines.h"
#include "Abilities/Skill/MUGA_ActivateSkill.h"

void FMUStepActionBase::OnStepIncreased(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_IF_INVALID(SkillAbility);
}

void FMUStepAction_JumpToMontage::OnStepIncreased(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_IF_INVALID(SkillAbility);
	
	FMUStepActionBase::OnStepIncreased(SkillAbility);
	SkillAbility->SetMontageSection(TargetToJumpMontageSection);
}

void FMUStepAction_SetTimer::OnStepIncreased(UMUGA_ActivateSkill* SkillAbility)
{
	RETURN_IF_INVALID(SkillAbility);
	
	FMUStepActionBase::OnStepIncreased(SkillAbility);
	SkillAbility->SetupAbilityStepTimer(TargetTime, bNeedToIncreaseStepWhenEnd);
}
