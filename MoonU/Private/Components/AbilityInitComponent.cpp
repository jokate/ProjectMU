// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilityInitComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Data/DataTable/MUData.h"
#include "Library/MUFunctionLibrary.h"


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
	Super::EndPlay(EndPlayReason);
}

void UAbilityInitComponent::InitAbilities(int32 CharacterID)
{
	const auto* AbilityUser = GetOwner<IAbilitySystemInterface>();

	if (!AbilityUser)
	{
		return; 
	}

	UAbilitySystemComponent* ASC = AbilityUser->GetAbilitySystemComponent();

	FMUCharacterInfo CharacterInfo;
	UMUFunctionLibrary::GetCharacterInfoData( GetOwner(), CharacterID, CharacterInfo);
	
	for (const auto& StartAbility : CharacterInfo.StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}

	for (const auto& StartAbility : CharacterInfo.NeedToStartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbilityAndActivateOnce(StartSpec);
	}
	
	for (const auto& InfiniteGameplayEffect : CharacterInfo.InfiniteGameplayEffects)
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

void UAbilityInitComponent::OnEndPlay(int32 CharacterID)
{
	const auto* AbilityUser = GetOwner<IAbilitySystemInterface>();

	if (!AbilityUser)
	{
		return; 
	}

	UAbilitySystemComponent* ASC = AbilityUser->GetAbilitySystemComponent();

	if (IsValid(ASC) == false)
	{
		return;
	}

	FMUCharacterInfo CharacterInfo;
	UMUFunctionLibrary::GetCharacterInfoData( GetOwner(), CharacterID, CharacterInfo);
	
	for (const auto& NeedToStopAbility : CharacterInfo.NeedToStartAbilities)
	{
		FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(NeedToStopAbility);

		if (AbilitySpec == nullptr)
		{
			continue;
		}
		
		ASC->CancelAbility(AbilitySpec->Ability);
	}
}


