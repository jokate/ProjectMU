// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_CastSkill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Data/MUStruct.h"
#include "Interface/SkillManager.h"
#include "Library/MUFunctionLibrary.h"

UMUGA_CastSkill::UMUGA_CastSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_CastSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* OwnerActor = ActorInfo->AvatarActor.Get();

	if ( IsValid(OwnerActor) == false )
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ISkillManager* SkillManager = Cast<ISkillManager>(OwnerActor);

	if ( SkillManager == nullptr )
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FName SkillID = SkillManager->GetSkillIDBySlot( CastSkillSlotType );

	FMUSkillData SkillData;
	if ( UMUFunctionLibrary::GetSkillData( OwnerActor, SkillID, SkillData) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Skill Is Not Valid"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 스킬을 땡긴다. ( Instant면 해당 관련 어빌리티가 즉각적으로 트리거 될 것입니다. )
	UAbilitySystemComponent* OwnerASC = GetAbilitySystemComponentFromActorInfo();

	if ( IsValid(OwnerASC) == false )
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FGameplayEventData_Skill EventDataSkill;
	
	EventDataSkill.CastingRange = SkillData.CastingRange;
	EventDataSkill.IndicatorClass = SkillData.SkillIndicatorClass;

	OwnerASC->HandleGameplayEvent(SkillData.SkillGameplayTag, &EventDataSkill);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
