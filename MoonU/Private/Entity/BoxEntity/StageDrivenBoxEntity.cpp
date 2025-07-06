// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/BoxEntity/StageDrivenBoxEntity.h"

#include "GameFramework/GameModeBase.h"
#include "Interface/StageManager.h"


// Sets default values
AStageDrivenBoxEntity::AStageDrivenBoxEntity()
{
}

void AStageDrivenBoxEntity::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (IsValid(GM) == false)
	{
		return;
	}

	IStageManager* StageManager = Cast<IStageManager>(GM);

	if ( StageManager == nullptr )
	{
		return;		
	}

	FOnStageEvents& StageEvents = StageManager->GetStageEvents();

	StageEvents.OnStageStarted.AddDynamic( this , &AStageDrivenBoxEntity::OnActiveStage);
}

void AStageDrivenBoxEntity::SettingUpInformation()
{
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (IsValid(GM) == false)
	{
		return;
	}

	IStageManager* StageManager = Cast<IStageManager>(GM);

	if ( StageManager == nullptr )
	{
		return;
	}

	if ( StageManager->IsStageActiveOrCleared( StageID ) == true )
	{
		return;
	}
	
	Super::SettingUpInformation();
}

void AStageDrivenBoxEntity::OnActiveStage(FName StageName)
{
	if ( CheckTimerHandle.IsValid() == true )
	{
		GetWorldTimerManager().ClearTimer(CheckTimerHandle);
	}
}

void AStageDrivenBoxEntity::OnClearStage(FName ClearedStage)
{
}

void AStageDrivenBoxEntity::OnBoxInBound()
{
	Super::OnBoxInBound();

	AGameModeBase* GM = GetWorld()->GetAuthGameMode();

	if (IsValid(GM) == false)
	{
		return;
	}

	IStageManager* StageManager = Cast<IStageManager>(GM);
	
	if ( StageManager == nullptr )
	{
		return;		
	}

	StageManager->StartStage( StageID );
}
