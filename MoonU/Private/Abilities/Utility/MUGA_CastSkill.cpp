// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_CastSkill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Interface/SkillManager.h"
#include "Library/MUFunctionLibrary.h"

void UMUGA_CastSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* OwnerActor = ActorInfo->AvatarActor.Get();

	if ( IsValid(OwnerActor) == false )
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	ISkillManager* SkillManager = Cast<ISkillManager>(OwnerActor);

	if ( SkillManager == nullptr )
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	FName SkillID = SkillManager->GetSkillIDBySlot( CastSkillSlotType );

	FMUSkillData SkillData;
	if ( UMUFunctionLibrary::GetSkillData( OwnerActor, SkillID, SkillData) == false)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	switch (SkillData.CastingType)
	{
	case ESkillCastingType::Indicator :
		{
			// 스킬 캐스팅 용 Task 생성.
			break;
		}

	case ESkillCastingType::Instant :
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, SkillData.SkillGameplayTag, FGameplayEventData());
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			break;
		}
	}
}

void UMUGA_CastSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
