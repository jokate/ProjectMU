// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_CreateItemEntity.h"

UMUAT_CreateItemEntity* UMUAT_CreateItemEntity::CreateTask(UGameplayAbility* InAbility, FName InItemDropPoolID)
{
	UMUAT_CreateItemEntity* NewTask = NewAbilityTask<UMUAT_CreateItemEntity>(InAbility);
	NewTask->ItemDropPoolID = InItemDropPoolID;

	return NewTask;
}

void UMUAT_CreateItemEntity::Activate()
{
	Super::Activate();


	// 해당 부분에서 데이터를 기반으로 해서 아이템 Entity를 생성해줘야 한다고 생각한다.
}

void UMUAT_CreateItemEntity::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
