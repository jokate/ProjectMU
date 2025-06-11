// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Utility/MUGA_HitReaction.h"

#include "Interface/MotionWarpTarget.h"

UMUGA_HitReaction::UMUGA_HitReaction()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_HitReaction::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const FGameplayAbilityTargetData* EventData = TriggerEventData->TargetData.Get(0);

	if ( EventData != nullptr && bUseMotionWarp == true )
	{
		AActor* OwnerActor = GetOwningActorFromActorInfo();
	
		IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(OwnerActor);

		const FHitResult* HitResult = EventData->GetHitResult();

		if ( HitResult != nullptr && MotionWarp != nullptr )
		{
			FVector Direction = HitResult->ImpactPoint - OwnerActor->GetActorLocation();
			FVector Point = HitResult->ImpactPoint;

			FRotator Rotation = Direction.Rotation();
			Rotation.Pitch = 0.f;
			Rotation.Roll = 0.f;
			
			MotionWarp->SetMotionWarpToCursorDirection(MotionWarpName, MotionWarpType, Point, Rotation );
		}
	}

}

void UMUGA_HitReaction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AActor* OwnerActor = GetOwningActorFromActorInfo();
	
	IMotionWarpTarget* MotionWarp = Cast<IMotionWarpTarget>(OwnerActor);
		
	if (MotionWarp != nullptr)
	{
		MotionWarp->ReleaseMotionWarp(MotionWarpName);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
