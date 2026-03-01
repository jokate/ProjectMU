// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_Trace.h"

#include "AbilitySystemComponent.h"
#include "Abilities/TA/MUTA_Trace.h"

UMUAT_Trace::UMUAT_Trace()
{
	
}

UMUAT_Trace* UMUAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<AMUTA_Trace> TargetActorClass, const FName& TargetDamageInfo )
{
	UMUAT_Trace* NewTask = NewAbilityTask<UMUAT_Trace>(OwningAbility);
	NewTask->TargetActorClass = TargetActorClass;
	NewTask->TargetDamageInfo = TargetDamageInfo;
	return NewTask;
}

void UMUAT_Trace::Activate()
{
	Super::Activate();
	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();

	SetWaitingOnAvatar();
}

void UMUAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_Trace::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<AMUTA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity,
	nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));

	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UMUAT_Trace::OnTargetDataReadyCallback);
		SpawnedTargetActor->InitializeData(TargetDamageInfo);
	}

	SpawnedTargetActor->FinishSpawning(FTransform::Identity);
}

void UMUAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);

		SpawnedTargetActor->StartTargeting(Ability);
	}
}

void UMUAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnComplete.Broadcast(DataHandle);
	}

	EndTask();
}
