// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUGameMode.h"

#include "Character/MUCharacterPlayer.h"
#include "Components/StageManagingComponent.h"
#include "Components/TimeStopManager.h"
#include "Components/TimeWindManager.h"

AMUGameMode::AMUGameMode()
{
	TimeWindManager = CreateDefaultSubobject<UTimeWindManager>(TEXT("TimeWindManager"));
	TimeStopManager = CreateDefaultSubobject<UTimeStopManager>(TEXT("TimeStopManager"));
	StageManagingComponent = CreateDefaultSubobject<UStageManagingComponent>(TEXT("StageManagingComponent"));
}

void AMUGameMode::TimeWindActivate()
{
	TimeWindManager->TimeWindActivate();
}

void AMUGameMode::TimeWindDeactivate()
{
	TimeWindManager->TimeWindDeactivate();
}

void AMUGameMode::RegisterTimeWindTarget(AActor* InActor)
{
	TimeWindManager->RegisterTimeWindTarget(InActor);
}

void AMUGameMode::UnregisterTimeWindTarget(AActor* InActor)
{
	TimeWindManager->UnregisterTimeWindTarget(InActor);
}

void AMUGameMode::TimeStopActivate()
{
	TimeStopManager->TimeStopActivate();
}

void AMUGameMode::TimeStopDeactivate()
{
	TimeStopManager->TimeStopDeactivate();
}

void AMUGameMode::RegisterTimerStopTarget(AActor* InActor)
{
	TimeStopManager->RegisterTimerStopTarget(InActor);
}

void AMUGameMode::UnregisterTimeStopTarget(AActor* InActor)
{
	TimeStopManager->UnregisterTimeStopTarget(InActor);
}

void AMUGameMode::RegisterOwnerActor(AActor* LocalPlayer)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return;
	}

	StageManagingComponent->RegisterOwnerActor(LocalPlayer);
}

void AMUGameMode::SendClearSpawner(FName ClearedSpawnID)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return;
	}

	StageManagingComponent->SendClearSpawner( ClearedSpawnID );
}

bool AMUGameMode::IsSpawnerCleared(FName SpawnerID)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return false;
	}

	return StageManagingComponent->IsSpawnerCleared( SpawnerID );
}

void AMUGameMode::CheatSetupEnforcement(int32 EnforcementID)
{
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();

	if (IsValid(MyPlayerController) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("My Player Controller Is Not Valid"));
		return;
	}

	AMUCharacterPlayer* CurrentPlayer = MyPlayerController->GetPawn<AMUCharacterPlayer>();

	if ( IsValid(CurrentPlayer) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("My Player Is Not Valid"));
		return;
	}

	CurrentPlayer->EnforcementUnit(EnforcementID);
}

void AMUGameMode::CheatLevelUp()
{
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();

	if (IsValid(MyPlayerController) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("My Player Controller Is Not Valid"));
		return;
	}

	AMUCharacterPlayer* CurrentPlayer = MyPlayerController->GetPawn<AMUCharacterPlayer>();

	if ( IsValid(CurrentPlayer) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("My Player Is Not Valid"));
		return;
	}

	CurrentPlayer->LevelUp();

	
}
