// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_IndicatorSkill.h"

#include "Components/Input/MUEnhancedInputComponent.h"
#include "Library/MUFunctionLibrary.h"

void UMUGA_IndicatorSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Input에 대한 바인딩 처리 필요.
	AActor* OwnerActor = GetAvatarActorFromActorInfo();

	if ( IsValid(OwnerActor) == false )
	{
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(OwnerActor);

	if ( IsValid( OwnerPawn ) == false )
	{
		return;
	}
	
	UMUEnhancedInputComponent* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(OwnerActor->InputComponent);

	if ( IsValid( EnhancedInputComponent ) == false )
	{
		return;
	}
	
	UInputConfig* InputConfig = UMUFunctionLibrary::GetInputConfigByOwner( GetAvatarActorFromActorInfo() );
	//EnhancedInputComponent->BindActionByTag( InputConfig, IndicatorInput.InputTag, SkillInput.TriggerEvent, this,  );
}

void UMUGA_IndicatorSkill::SkillTriggered(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::SkillTriggered(Handle, ActorInfo, ActivationInfo);

	ActivateSkill();
}

void UMUGA_IndicatorSkill::OnSkillInputPressed()
{
}

void UMUGA_IndicatorSkill::OnSkillCanceled()
{
}
