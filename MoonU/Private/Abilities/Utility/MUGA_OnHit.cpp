// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_OnHit.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Interface/Defender.h"

UMUGA_OnHit::UMUGA_OnHit()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AngleMargin = 60.0f;
}

void UMUGA_OnHit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//꾸준하게 돌아가는 Ability -- 기능상 HitChecker의 기능.
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//해당 Ability는 Hit 정보 및 현재 플레이어의 방어 및 패리에 관한 정보를 기반으로 동작을 확립한다.
	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor == nullptr)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (ASC == nullptr)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
	
	ASC->GenericGameplayEventCallbacks.FindOrAdd(TriggerGameplayTag).AddUObject(this, &UMUGA_OnHit::OnHitCheckedCallback);
}

void UMUGA_OnHit::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	//해당 Ability는 Hit 정보 및 현재 플레이어의 방어 및 패리에 관한 정보를 기반으로 동작을 확립한다.
	AActor* TargetActor = ActorInfo->AvatarActor.Get();

	if (TargetActor)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

		if (ASC)
		{
			ASC->GenericGameplayEventCallbacks.Remove(TriggerGameplayTag);
		}
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMUGA_OnHit::OnHitCheckedCallback(const FGameplayEventData* EventData)
{
	//hit에 따른 정보를 기반으로 타 어빌리티를 호출할 수 있도록 한다..

	const FGameplayAbilityTargetData* TargetData = EventData->TargetData.Get(0);

	if (TargetData == nullptr)
	{
		return;
	}

	const FHitResult* HitResult = TargetData->GetHitResult();

	if (HitResult == nullptr)
	{
		return;
	}
	
	// Hit에 관한 부분을 수행한다.
	AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();

	if (AvatarActor == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AvatarActor);

	if (ASC == nullptr)
	{
		return;
	}

	IDefender* Defender = Cast<IDefender>(AvatarActor);

	const FVector DefendRange = Defender->GetDefendRange();
	const FTransform DefendTransform = Defender->GetDefendTransform();

	bool bCanDefend = ASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_PARRY) || ASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_DEFENDING);
	bCanDefend &= CheckHitLocationIsInDefendBound(DefendTransform, HitResult->ImpactPoint, DefendRange);
	bCanDefend &= CheckHitInstigatorActorInProperAngle(AvatarActor, EventData->Instigator);

	FGameplayTagContainer DodgeTagContainer;
	DodgeTagContainer.AddTag(MU_CHARACTERSTATE_DODGE);
	DodgeTagContainer.AddTag(MU_CHARACTERSTATE_PERFECTDODGE);
 	bool bPerfectDodge = ASC->HasAllMatchingGameplayTags(DodgeTagContainer);

	if (bPerfectDodge)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AvatarActor, MU_CHARACTERSTATE_PERFECTDODGE_COMPLETE, *EventData);
		return;
	}
	if (bCanDefend)
	{
		for (const FGameplayTag& DefendRelatedTag : DefendStateTag)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AvatarActor, DefendRelatedTag, *EventData);
		}
	}
	else
	{
		for (const FGameplayTag& UndefendRelatedTag : UnDefendStateTag)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AvatarActor, UndefendRelatedTag, *EventData);
		}
	}
}

bool UMUGA_OnHit::CheckHitLocationIsInDefendBound(const FTransform& InTransform, const FVector& HitLocation, const FVector& Extent)
{
	const FVector LocalSpaceLocation = InTransform.InverseTransformPosition(HitLocation);

	const float MaxZ = Extent.Z;
	const float MinZ = -Extent.Z;
	const float MaxX = Extent.X;
	const float MinX = -Extent.X;
	const float MaxY = Extent.Y;
	const float MinY = -Extent.Y;


	const bool bContainZ = LocalSpaceLocation.Z > MinZ && LocalSpaceLocation.Z <= MaxZ;
	const bool bContainY = LocalSpaceLocation.Y > MinY && LocalSpaceLocation.Y <= MaxY;
	const bool bContainX = LocalSpaceLocation.X > MinX && LocalSpaceLocation.X <= MaxX;

	return bContainX && bContainY && bContainZ;
}

bool UMUGA_OnHit::CheckHitInstigatorActorInProperAngle(const AActor* CurrentActor, const AActor* InstigatorActor)
{
	const FVector& CurrentActorFrontward = CurrentActor->GetActorForwardVector().GetSafeNormal2D();
	const FVector& CurrentActorLocation = CurrentActor->GetActorLocation();

	const FVector& InstigatorLocation = InstigatorActor->GetActorLocation();


	const FVector DirectionToInstigator = (InstigatorLocation - CurrentActorLocation).GetSafeNormal2D();


	const float DotProduct = CurrentActorFrontward.Dot(DirectionToInstigator);

	const float Angle = FMath::Acos(DotProduct) * (180 / PI);

	return Angle <= AngleMargin;
}
