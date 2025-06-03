// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUAbilitySystemComponent.h"

#include "Abilities/Skill/MUGA_ActivateSkill.h"


// Sets default values for this component's properties
UMUAbilitySystemComponent::UMUAbilitySystemComponent()
{

}


void UMUAbilitySystemComponent::AllocateSkill(FName SkillID, const FGameplayAbilitySpec& AbilitySpec)
{
	// 실질적인 Ability 할당.
	FGameplayAbilitySpecHandle SpecHandle = GiveAbility( AbilitySpec );

	SkillAbilitySpec.Add( SkillID, SpecHandle );
}

void UMUAbilitySystemComponent::DeallocateSkill(FName SkillID)
{
	if ( SkillAbilitySpec.Contains( SkillID ) == true )
	{
		FGameplayAbilitySpecHandle AbilitySpec = SkillAbilitySpec[SkillID];

		ClearAbility(AbilitySpec);
	}
}

FGameplayAbilitySpec* UMUAbilitySystemComponent::FindAbilitySpecBySkillID(FName SkillID)
{
	if ( SkillAbilitySpec.Contains( SkillID ) == false )
	{
		return nullptr;
	}
	
	return FindAbilitySpecFromHandle( SkillAbilitySpec[SkillID] );
}

void UMUAbilitySystemComponent::TryTriggerSkill(FName SkillID)
{
	const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecBySkillID( SkillID );
	if ( AbilitySpec == nullptr )
	{
		return;
	}

	// instanced per actor를 전제로 만든다.
	UMUGA_ActivateSkill* ActivateSkill = Cast<UMUGA_ActivateSkill>(AbilitySpec->Ability);

	if ( IsValid( ActivateSkill ) == true )
	{
		// 스킬 타입 별로 관련 데이터 세팅하는 것이 좋아보인다는 생각이 든다.
		ActivateSkill->SkillTriggered( AbilitySpec->Handle, AbilityActorInfo.Get(), AbilitySpec->ActivationInfo );
	}
}

void UMUAbilitySystemComponent::TryCancelSkill(FName SkillID)
{
	const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecBySkillID( SkillID );
	if ( AbilitySpec == nullptr )
	{
		return;
	}

	// instanced per actor를 전제로 만든다.
	UMUGA_ActivateSkill* ActivateSkill = Cast<UMUGA_ActivateSkill>(AbilitySpec->Ability);

	if ( IsValid( ActivateSkill ) == true )
	{
		// 스킬 타입 별로 관련 데이터 세팅하는 것이 좋아보인다는 생각이 든다.
		ActivateSkill->SkillUnTriggered( AbilitySpec->Handle, AbilityActorInfo.Get(), AbilitySpec->ActivationInfo );
	}
}
