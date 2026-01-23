// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_SetTimerAndWait.h"

UMUAT_SetTimerAndWait* UMUAT_SetTimerAndWait::CreateTask(UGameplayAbility* TargetAbility, float TimerToAction)
{
	UMUAT_SetTimerAndWait* Task = NewAbilityTask<UMUAT_SetTimerAndWait>(TargetAbility);
	Task->TimeToWait = TimerToAction;
	return Task;
}

void UMUAT_SetTimerAndWait::OnTimerEnd()
{
	if ( OnFinished.IsBound() )
	{
		OnFinished.Execute();
	}
}

void UMUAT_SetTimerAndWait::Activate()
{
	Super::Activate();
	
	GetWorld()->GetTimerManager().SetTimer(WaitTimeHandle, this, &UMUAT_SetTimerAndWait::OnTimerEnd, TimeToWait, false);
}

void UMUAT_SetTimerAndWait::OnDestroy(bool bInOwnerFinished)
{
	GetWorld()->GetTimerManager().ClearTimer(WaitTimeHandle);
	Super::OnDestroy(bInOwnerFinished);
}
