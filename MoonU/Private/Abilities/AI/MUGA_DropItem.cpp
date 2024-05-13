// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AI/MUGA_DropItem.h"

#include "Entity/InteractableEntity/ItemEntity.h"

UMUGA_DropItem::UMUGA_DropItem()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UMUGA_DropItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AbilityActor = ActorInfo->AvatarActor.Get();

	if (AbilityActor == nullptr)
	{
		return;
	}
	// 해당 부분에서 데이터를 기반으로 해서 아이템 Entity를 생성해줘야 한다고 생각한다.
	AItemEntity* Entity = GetWorld()->SpawnActorDeferred<AItemEntity>(ItemEntityClass, AbilityActor->GetActorTransform());
	Entity->OnInitialize(ItemDropName);

	Entity->FinishSpawning(AbilityActor->GetActorTransform());

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
