// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_CheckGoldenTime.h"

#include "Interface/TimerWindTarget.h"

UMUAT_CheckGoldenTime::UMUAT_CheckGoldenTime()
{
	
	bTickingTask = true;
}

UMUAT_CheckGoldenTime* UMUAT_CheckGoldenTime::CreateNewTask(UGameplayAbility* InAbility, float InGoldenTimeRate)
{
	UMUAT_CheckGoldenTime* GoldenTimeTask = NewAbilityTask<UMUAT_CheckGoldenTime>(InAbility);
	GoldenTimeTask->GoldenTimeRate = InGoldenTimeRate;
	GoldenTimeTask->bGoldenTimeTicking = true;
	return GoldenTimeTask;
}

void UMUAT_CheckGoldenTime::Activate()
{
	Super::Activate();

	AActor* TargetAvatarActor = Ability->GetAvatarActorFromActorInfo();

	if (TargetAvatarActor == nullptr)
	{
		return;
	}

	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(TargetAvatarActor);

	if (TimeWindTarget == nullptr)
	{
		return;
	}
	TimeWindTarget->GetTimeWindStateChangeEvent().AddUObject(this, &UMUAT_CheckGoldenTime::OnTimeWindChanged);
}

void UMUAT_CheckGoldenTime::OnDestroy(bool bInOwnerFinished)
{
	AActor* TargetAvatarActor = Ability->GetAvatarActorFromActorInfo();

	if (TargetAvatarActor == nullptr)
	{
		return;
	}
	
	ITimeWindTarget* TimeWindTarget = Cast<ITimeWindTarget>(TargetAvatarActor);

	if (TimeWindTarget == nullptr)
	{
		return;
	}
	
	TimeWindTarget->GetTimeWindStateChangeEvent().RemoveAll(this);
	
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_CheckGoldenTime::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (bGoldenTimeTicking)
	{
		CurrentGoldenTime = FMath::Clamp(CurrentGoldenTime + DeltaTime, 0.0f, GoldenTimeRate);

		if (CurrentGoldenTime >= GoldenTimeRate)
		{
			GoldenTimeSatisfied.Broadcast();
		}
		
	}
	else
	{
		CurrentGoldenTime = FMath::Clamp(CurrentGoldenTime - DeltaTime, 0.0f, GoldenTimeRate);
	}
}

void UMUAT_CheckGoldenTime::OnTimeWindChanged(bool InTimeChanged)
{
	bGoldenTimeTicking = !InTimeChanged;
}
