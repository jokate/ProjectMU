// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_AddTagTemporary.h"

#include "AbilitySystemComponent.h"

UMUAT_AddTagTemporary* UMUAT_AddTagTemporary::CreateTask(UGameplayAbility* Ability, FGameplayTagContainer AddTag)
{
	UMUAT_AddTagTemporary* NewTask = NewAbilityTask<UMUAT_AddTagTemporary>(Ability);
	NewTask->AddingTag = AddTag;
	return NewTask;
}

void UMUAT_AddTagTemporary::Activate()
{
	Super::Activate();

	UAbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();

	if ( IsValid(ASC) == true)
	{
		ASC->AddLooseGameplayTags( AddingTag );
	}
}
