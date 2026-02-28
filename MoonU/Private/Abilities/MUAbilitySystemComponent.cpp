// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Skill/MUGA_ActivateSkill.h"


// Sets default values for this component's properties
UMUAbilitySystemComponent::UMUAbilitySystemComponent()
{

}

UMUAbilitySystemComponent* UMUAbilitySystemComponent::Get(AActor* InActor)
{
	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(InActor);
	if (!ASI)
	{
		return nullptr;
	}

	return Cast<UMUAbilitySystemComponent>(ASI->GetAbilitySystemComponent());
}


void UMUAbilitySystemComponent::AllocateSkill(FName SkillID, const FGameplayAbilitySpec& AbilitySpec)
{
	// 실질적인 Ability 할당.
	FGameplayAbilitySpecHandle SpecHandle = Super::GiveAbility( AbilitySpec );

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

	// 만약 해당 Spec이 비활성화 중이라는 가정
	if ( AbilitySpec->IsActive() == false )
	{
		TryActivateAbility( AbilitySpec->Handle );
	}
	else
	{
		UMUGA_ActivateSkill* ActivateSkill = Cast<UMUGA_ActivateSkill>(AbilitySpec->GetPrimaryInstance());

		if ( IsValid(ActivateSkill) == true )
		{
			ActivateSkill->SkillTriggered( AbilitySpec->Handle, AbilityActorInfo.Get(), ActivateSkill->GetCurrentActivationInfo() );			
		}
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
		ActivateSkill->SkillUnTriggered( AbilitySpec->Handle, AbilityActorInfo.Get(), ActivateSkill->GetCurrentActivationInfo() );
	}
}

void UMUAbilitySystemComponent::GiveAbility(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& InputTag)
{
	FGameplayAbilitySpecHandle AbilitySpecHandle = Super::GiveAbility(AbilitySpec);

	// 어빌리티 스펙 핸들 추가.
	AddAbilitySpecWithTag(InputTag, AbilitySpecHandle);	
}

void UMUAbilitySystemComponent::AddAbilitySpecWithTag(const FGameplayTag& InputGameplayTag,
                                                      FGameplayAbilitySpecHandle& AbilitySpec)
{
	InputAbilitySpecHandle.Emplace(InputGameplayTag, AbilitySpec);
}

FGameplayAbilitySpec* UMUAbilitySystemComponent::GetAbilityByInputTag(const FGameplayTag& InputGameplayTag)
{
	const FGameplayAbilitySpecHandle* AbilitySpecHandle =  InputAbilitySpecHandle.Find(InputGameplayTag);

	if ( AbilitySpecHandle == nullptr )
	{
		return nullptr;
	}

	return FindAbilitySpecFromHandle(*AbilitySpecHandle);
}
