// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Action/MUGA_Rollout.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/MUCharacterPlayer.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSet.h"
#include "Components/CapsuleComponent.h"

UMUGA_Rollout::UMUGA_Rollout()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_Rollout::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AMUCharacterPlayer* Character = Cast<AMUCharacterPlayer>(ActorInfo->AvatarActor.Get());

	if (Character == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();

	if (!ASC)
	{
		return;
	}
	const float CurrentStamina = ASC->GetNumericAttribute(UMUCharacterAttributeSet::GetCurrentStaminaAttribute());
	ASC->AddLooseGameplayTag(MU_EVENT_BLOCKRECOVER);
	
	FVector2D RecentlyMoved = Character->GetRecentlyMovedVector().GetSafeNormal();

	int32 Sign = RecentlyMoved.X > 0.0f ? 1 : -1;
 	
	if (RecentlyMoved.IsNearlyZero() || CurrentStamina < MinStaminaToUse)
	{
		//명시적으로 Ability가 끝났음을 알림
		bool bReplicatedEndAbility = true;
		bool bWasCancelled = false;
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
		return;
	}

	
	float Angle = FMath::RadiansToDegrees(acosf(FVector2D::DotProduct(RecentlyMoved, FVector2D(0, 1)))) * Sign;
	FName SectionName = GetCurrentMontageSection(Angle);
	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DODGE"), AnimMontageForRollOut, 1.0f, SectionName);
	
	NewTask->OnCompleted.AddDynamic(this, &UMUGA_Rollout::OnCompleteCallback);
	NewTask->OnInterrupted.AddDynamic(this, &UMUGA_Rollout::OnInterruptedCallback);
	NewTask->OnCancelled.AddDynamic(this, &UMUGA_Rollout::OnInterruptedCallback);
	NewTask->OnBlendOut.AddDynamic(this, &UMUGA_Rollout::OnInterruptedCallback);

	NewTask->ReadyForActivation();
	
}

void UMUGA_Rollout::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UMUGA_Rollout::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AMUCharacterPlayer* Character = Cast<AMUCharacterPlayer>(ActorInfo->AvatarActor.Get());
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorInfo->AvatarActor.Get());

	if (!ASC)
	{
		return;
	}

	ASC->RemoveLooseGameplayTag(MU_EVENT_BLOCKRECOVER);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_Rollout::OnCompleteCallback()
{
	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UMUGA_Rollout::OnInterruptedCallback()
{	//명시적으로 Ability가 끝났음을 알림
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

const FName UMUGA_Rollout::GetCurrentMontageSection(float RecentedInput)
{
	if (-22.5f <= RecentedInput && RecentedInput <= 22.5f)
	{
		return MontageSectionMap[Frontward];
	}

	if (22.5f < RecentedInput && RecentedInput <= 67.5f)
	{
		return MontageSectionMap[FrontwardRight];
	}

	if (67.5f < RecentedInput && RecentedInput <= 112.5f)
	{
		return MontageSectionMap[Right];
	}

	if (112.5f < RecentedInput && RecentedInput <= 157.5f)
	{
		return MontageSectionMap[BackwardRight];
	}

	if (157.5f < RecentedInput && RecentedInput <= -157.5f)
	{
		return MontageSectionMap[Backward];
	}

	if (-157.5f < RecentedInput &&  RecentedInput <= -112.5f)
	{
		return MontageSectionMap[BackwardLeft];
	}

	if (-112.5f< RecentedInput &&  RecentedInput <= -67.5f)
	{
		return MontageSectionMap[Left];
	}
	
	if (-67.5f < RecentedInput &&  RecentedInput <=22.5f)
	{
		return MontageSectionMap[FrontwardLeft];
	}

	return FName();
}



