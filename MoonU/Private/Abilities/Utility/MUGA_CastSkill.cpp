// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_CastSkill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/AT/MUAT_ShowIndicator.h"
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

	switch (SkillData.CastingType)
	{
	case ESkillCastingType::Indicator :
		{
			// 스킬 캐스팅 용 Task 생성.
			UMUAT_ShowIndicator* IndicatorTask = UMUAT_ShowIndicator::CreateTask( this, SkillData.SkillIndicatorType, SkillData.CastingRange );
			IndicatorTask->ReadyForActivation();
			//저렇게 되는 경우 세팅 필요. -> 인풋에 대한 교체 작업 필요하다. (필수적인 구현사항)
			//단, Ability에 대한 세팅..?
			break;
		}

	case ESkillCastingType::Instant :
		{
			// 만약 즉각적으로 스킬을 사용하는 경우에는 즉시적인 스킬 사용
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, SkillData.SkillGameplayTag, FGameplayEventData());
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			break;
		}
	default:
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		}
	}
	
}

void UMUGA_CastSkill::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMUGA_CastSkill::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);

	if ( bIsCastingSkill )
	{
		// 인디케이터가 있는 경우 관련 방향으로 세팅 후 조정해줘야 함.
		AActor* OwnerActor = ActorInfo->AvatarActor.Get();

		if ( IsValid(OwnerActor) == false )
		{
			return;
		}
	}
	
}
