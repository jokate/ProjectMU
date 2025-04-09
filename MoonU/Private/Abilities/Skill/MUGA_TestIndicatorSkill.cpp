// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_TestIndicatorSkill.h"

void UMUGA_TestIndicatorSkill::ActivateSkill()
{
	Super::ActivateSkill();

	UE_LOG(LogTemp, Log, TEXT("Indicator Skill Activated"));

	EndAbility( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false );
}
