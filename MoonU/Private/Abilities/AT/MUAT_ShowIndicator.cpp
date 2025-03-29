// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_ShowIndicator.h"

UMUAT_ShowIndicator* UMUAT_ShowIndicator::CreateTask(UGameplayAbility* Ability, ESkillIndicatorType SkillIndicatorType, float SkillDistance )
{
	UMUAT_ShowIndicator* IndicatorTask = NewAbilityTask<UMUAT_ShowIndicator>(Ability);

	IndicatorTask->IndicatorType = SkillIndicatorType;
	IndicatorTask->SkillDistance = SkillDistance;

	return IndicatorTask;
}
