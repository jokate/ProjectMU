// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_SetTimerAndWait.h"

UMUAT_SetTimerAndWait* UMUAT_SetTimerAndWait::CreateTask(UGameplayAbility* TargetAbility, float TimerToAction, bool bInNeedToIncrementStep)
{
	UMUAT_SetTimerAndWait* Task = NewAbilityTask<UMUAT_SetTimerAndWait>(TargetAbility);
	Task->TimeToWait = TimerToAction;
	Task->bNeedToIncrementStep = bInNeedToIncrementStep;
	return Task;
}

void UMUAT_SetTimerAndWait::OnTimerEnd()
{
	if ( OnFinished.IsBound() )
	{
		OnFinished.Execute(bNeedToIncrementStep);
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
