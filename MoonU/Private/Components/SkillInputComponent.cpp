// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkillInputComponent.h"


// Sets default values for this component's properties
USkillInputComponent::USkillInputComponent()
{
}

void USkillInputComponent::TriggerSkill()
{
	if ( ActivateSkillEvent.IsBound() == true )
	{
		ActivateSkillEvent.Broadcast();
	}
}

void USkillInputComponent::CancelSkill()
{
	if ( DeactivateSkillEvent.IsBound() == true)
	{
		DeactivateSkillEvent.Broadcast();
	}
}