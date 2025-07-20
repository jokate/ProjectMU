// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_RemoveTag.h"

#include "AbilitySystemComponent.h"

UMUAT_RemoveTag* UMUAT_RemoveTag::CreateTask(UGameplayAbility* GameplayAbility, FGameplayTagContainer TagContainer)
{
	UMUAT_RemoveTag* Task = NewAbilityTask<UMUAT_RemoveTag>(GameplayAbility);

	Task->RemoveTagContainer = TagContainer;

	return Task;
}

void UMUAT_RemoveTag::Activate()
{
	Super::Activate();

	UAbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();

	if ( IsValid(ASC) == true)
	{
		ASC->RemoveLooseGameplayTags( RemoveTagContainer );
	}
}
