// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AT/MUAT_CheckGoldenTime.h"

#include "AbilitySystemComponent.h"
#include "MUDefines.h"
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

	CachedASC = Ability->GetAbilitySystemComponentFromActorInfo();

	if (CachedASC == nullptr)
	{
		return;
	}
}

void UMUAT_CheckGoldenTime::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UMUAT_CheckGoldenTime::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (!CachedASC->HasMatchingGameplayTag(MU_CHARACTERSTATE_TIMEWINDING))
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

