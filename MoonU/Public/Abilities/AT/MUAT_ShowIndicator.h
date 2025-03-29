// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Data/MUEnum.h"
#include "MUAT_ShowIndicator.generated.h"

/**
 * 
 */

// Purpose : Input에 대한 처리가 들어오기 전까지는 인디케이터를 보여줄 수 있도록 한다.
UCLASS()
class MOONU_API UMUAT_ShowIndicator : public UAbilityTask
{
	GENERATED_BODY()

public : 
	static UMUAT_ShowIndicator* CreateTask(UGameplayAbility* Ability, ESkillIndicatorType SkillIndicatorType, float SkillDistance);

	
public : 
	UPROPERTY()
	ESkillIndicatorType IndicatorType;

	UPROPERTY()
	float SkillDistance = 0;
};
