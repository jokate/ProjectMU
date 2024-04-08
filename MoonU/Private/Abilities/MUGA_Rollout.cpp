﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MUGA_Rollout.h"

#include "KismetAnimationLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UMUGA_Rollout::UMUGA_Rollout()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_Rollout::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());

	if (Character == nullptr)
	{
		return;
	}
	FVector NormalizedVector = Character->GetLastMovementInputVector().GetSafeNormal();
	float Angle = FMath::Acos(NormalizedVector.Dot(FVector(0, 1, 0))) * (180 / PI);
	FName SectionName = GetCurrentMontageSection(Angle);
	UAbilityTask_PlayMontageAndWait* NewTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("DODGE"), AnimMontageForRollOut, 1.0f, SectionName);

	NewTask->OnCompleted.AddDynamic(this, &UMUGA_Rollout::OnCompleteCallback);
	NewTask->OnInterrupted.AddDynamic(this, &UMUGA_Rollout::OnInterruptedCallback);

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

	if (-157.5 < RecentedInput &&  RecentedInput <= -112.5f)
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



