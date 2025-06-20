﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StageManagingComponent.h"

void UStageManagingComponent::StartStage(FName StageName)
{
	// 레벨로딩 혹은 실질적인 스테이지 액터 스포닝. (몬스터 스포너나 혹은 액티베이션)
	CurrentStageName = StageName;
	
	if ( OnStageStarted.IsBound() == true )
	{
		OnStageStarted.Broadcast(CurrentStageName);
	}
}

void UStageManagingComponent::EndStage()
{
	if ( OnStageCleared.IsBound() == true )
	{
		OnStageCleared.Broadcast( CurrentStageName );
	}
	
	CurrentStageName = NAME_None;
}

void UStageManagingComponent::RegisterUnit(FName UnitName)
{
	int32& UnitCount = StageCount.FindOrAdd(UnitName);

	UnitCount++;
}

void UStageManagingComponent::UnregisterUnit(FName UnitName)
{
	int32* UnitCount = StageCount.Find(UnitName);

	if ( UnitCount == nullptr)
	{
		return;
	}

	*UnitCount--;

	int32 CurrentValue = *UnitCount;

	if ( CurrentValue <= 0 )
	{
		StageCount.Remove(UnitName);

		if ( StageCount.Num() <= 0)
		{
			// 스테이지 클리어.
			EndStage();
		}
	}
}
