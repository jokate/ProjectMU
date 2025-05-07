// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_TestIndicatorSkill.h"

UMUGA_TestIndicatorSkill::UMUGA_TestIndicatorSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_TestIndicatorSkill::ActivateSkill()
{
	UE_LOG(LogTemp, Display, TEXT("Activate Skill"));
	Super::ActivateSkill();
}

void UMUGA_TestIndicatorSkill::CancelSkill()
{
	UE_LOG(LogTemp, Display, TEXT("Cancel Skill"));
	
	Super::CancelSkill();
}
