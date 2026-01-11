// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AbilityAnimNotify/MUAnimNotify_Ability.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

UGameplayAbility* UMUAnimNotify_Ability::GetCurrentAbility(USkeletalMeshComponent* MeshComponent) const
{
	AActor* Owner = MeshComponent->GetOwner();

	if ( IsValid(Owner) == false )
	{
		return nullptr;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);

	if  (IsValid(ASC) == false )
	{
		return nullptr;
	}

	return ASC->GetAnimatingAbility();
}
