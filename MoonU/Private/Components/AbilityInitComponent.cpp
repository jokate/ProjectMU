// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilityInitComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"


// Sets default values for this component's properties
UAbilityInitComponent::UAbilityInitComponent()
{
}


void UAbilityInitComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAbilityInitComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnEndPlay();
	
	Super::EndPlay(EndPlayReason);
}

void UAbilityInitComponent::InitAbilities()
{
	const auto* AbilityUser = GetOwner<IAbilitySystemInterface>();

	if (!AbilityUser)
	{
		return; 
	}

	UAbilitySystemComponent* ASC = AbilityUser->GetAbilitySystemComponent();
	
	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}
	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
		StartSpec.InputID = StartInputAbility.Key;
		ASC->GiveAbility(StartSpec);
	}

	for (const auto& StartAbility : NeedToStartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbilityAndActivateOnce(StartSpec);
	}
	
	for (const auto& InfiniteGameplayEffect : InfiniteGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = ASC->MakeOutgoingSpec(InfiniteGameplayEffect, 0, EffectContext);

		if (NewHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), ASC);
		}
	}
}

void UAbilityInitComponent::OnEndPlay()
{
	const auto* AbilityUser = GetOwner<IAbilitySystemInterface>();

	if (!AbilityUser)
	{
		return; 
	}

	UAbilitySystemComponent* ASC = AbilityUser->GetAbilitySystemComponent();
	
	for (const auto& NeedToStopAbility : NeedToStartAbilities)
	{
		FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(NeedToStopAbility);

		if (AbilitySpec == nullptr)
		{
			continue;
		}
		
		ASC->CancelAbility(AbilitySpec->Ability);
	}
}


