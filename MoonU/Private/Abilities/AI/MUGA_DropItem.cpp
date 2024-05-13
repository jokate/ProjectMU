// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_DropItem.h"

#include "Abilities/AT/MUAT_CreateItemEntity.h"

UMUGA_DropItem::UMUGA_DropItem()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_DropItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UMUAT_CreateItemEntity* NewTask = UMUAT_CreateItemEntity::CreateTask(this, ItemDropName);

	NewTask->ReadyForActivation();
}
