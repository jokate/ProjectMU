// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_CheckVelocity.h"

#include "GameFramework/Character.h"

UMUAT_CheckVelocity::UMUAT_CheckVelocity()
{
	bTickingTask = true;
}

UMUAT_CheckVelocity* UMUAT_CheckVelocity::CreateNewTask(UGameplayAbility* InAbility)
{
	UMUAT_CheckVelocity* RetTask = NewAbilityTask<UMUAT_CheckVelocity>(InAbility);

	return RetTask;
}

void UMUAT_CheckVelocity::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (CurrentCharacter->GetVelocity().IsNearlyZero())
	{
		MoveCompleted.Broadcast();
	}
}

void UMUAT_CheckVelocity::Activate()
{
	Super::Activate();
	CurrentCharacter = Cast<ACharacter>(GetAvatarActor());
}
