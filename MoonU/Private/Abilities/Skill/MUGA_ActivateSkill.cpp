// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Skill/MUGA_ActivateSkill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Interface/MotionWarpTarget.h"
#include "Library/MUFunctionLibrary.h"

UMUGA_ActivateSkill::UMUGA_ActivateSkill()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UMUGA_ActivateSkill::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	FMUSkillData TempSkill;
	if ( UMUFunctionLibrary::GetSkillData(ActorInfo->AvatarActor.Get(), SkillID, TempSkill) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("스킬 없음!"));
		return false;
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UMUGA_ActivateSkill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAbilitySystemComponent* ASC = Cast<UMUAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()));

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->ExecuteGameplayCue(GameplayCueTag);
		}

		ASC->AddActiveAbility(this);
	}
	
	UMUFunctionLibrary::GetSkillData(ActorInfo->AvatarActor.Get(), SkillID, SkillData);
}

void UMUGA_ActivateSkill::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	UMUAbilitySystemComponent* ASC = Cast<UMUAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get()));

	if ( IsValid(ASC) == true )
	{
		for (const FGameplayTag& GameplayCueTag : GameplayCueTags)
		{
			ASC->InvokeGameplayCueEvent(GameplayCueTag, EGameplayCueEvent::Removed);
		}

		ASC->RemoveActiveAbility(this);
	}

	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(ActorInfo->OwnerActor.Get());
	
	if (MotionWarp != nullptr)
	{
		MotionWarp->ReleaseMotionWarp(SkillData.MotionWarpName);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UMUGA_ActivateSkill::CanUseSkill()
{
	if ( CheckCooldown(CurrentSpecHandle, CurrentActorInfo ) == false )
	{
		return false;
	}

	if ( CheckCooldown(CurrentSpecHandle, CurrentActorInfo ) == false )
	{
		return false;
	}

	return true;
}

void UMUGA_ActivateSkill::CastSkill()
{
	if ( CanUseSkill() == false )
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false );
	}
	else
	{
		ActivateSkill();
	}
}

void UMUGA_ActivateSkill::ActivateSkill()
{
	ApplyCost( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo );
	ApplyCooldown( CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo );

	SetupAnimMontage();
	
	if ( OnSkillStateChanged.IsBound() == true )
	{
		OnSkillStateChanged.Broadcast();
	}
}

void UMUGA_ActivateSkill::CancelSkill()
{
	if ( OnSkillStateChanged.IsBound() == true )
	{
		OnSkillStateChanged.Broadcast();
	}
}

void UMUGA_ActivateSkill::SetMontageSection(FName MontageSectionName)
{
	MontageJumpToSection(MontageSectionName);	
}

void UMUGA_ActivateSkill::SkillTriggered(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// 여부에 따라서 스킬 트리거가 바로 Ability를 실행 할 수도 혹은 실행된 상태에서만 동작할 수도 있음.  ( 테스트 필요함 )
}

void UMUGA_ActivateSkill::SkillUnTriggered(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	CancelSkill();
	EndAbility( Handle, ActorInfo, ActivationInfo, true, true );
}

void UMUGA_ActivateSkill::SetupAnimMontage()
{
	AActor* OwnerActor = GetOwningActorFromActorInfo();
	
	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(OwnerActor);
	
	if (MotionWarp == nullptr)
	{
		return;
	}
	
	UAnimMontage* ActiveMontage = SkillData.ActiveSkillMontage.LoadSynchronous();

	if ( IsValid(ActiveMontage) == false )
	{
		return;
	} 
	
	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, SkillID, ActiveMontage,
		1.0f, NAME_None, true );
	
	NewTask->OnCompleted.AddDynamic(this, &UMUGA_ActivateSkill::OnCompleteCallback);
	NewTask->OnInterrupted.AddDynamic(this, &UMUGA_ActivateSkill::OnInterruptedCallback);
	NewTask->OnCancelled.AddDynamic(this, &UMUGA_ActivateSkill::OnInterruptedCallback);
	NewTask->OnBlendOut.AddDynamic(this, &UMUGA_ActivateSkill::OnInterruptedCallback);

	if ( SkillData.bUseMotionWarp == true)
	{
		MotionWarp->SetMotionWarpToCursorDirection(SkillData.MotionWarpName,SkillData.MotionWarpType, TargetLocation, TargetRotation );	
	}
	
	NewTask->ReadyForActivation();
}

void UMUGA_ActivateSkill::OnCompleteCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_ActivateSkill::OnInterruptedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}
