// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUGameMode.h"

#include "Character/MUCharacterPlayer.h"
#include "Components/MUEnforcementManageComponent.h"
#include "Components/MUObjectPoolingManager.h"
#include "Components/StageManagingComponent.h"
#include "Components/TimeStopManager.h"
#include "Components/TimeWindManager.h"
#include "DevSetting/MUDevSettings.h"

AMUGameMode::AMUGameMode()
{
	TimeWindManager = CreateDefaultSubobject<UTimeWindManager>(TEXT("TimeWindManager"));
	TimeStopManager = CreateDefaultSubobject<UTimeStopManager>(TEXT("TimeStopManager"));
	StageManagingComponent = CreateDefaultSubobject<UStageManagingComponent>(TEXT("StageManagingComponent"));
	EnforcementManageComponent = CreateDefaultSubobject<UMUEnforcementManageComponent>(TEXT("EnforcementManager"));
	ObjectPoolingManager = CreateDefaultSubobject<UMUObjectPoolingManager>(TEXT("ObjectPoolingManager"));
}

void AMUGameMode::BeginPlay()
{
	Super::BeginPlay();

	const UMUDevSettings* DevSetting = GetDefault<UMUDevSettings>();

	if ( IsValid(DevSetting) )
	{
		if ( DevSetting->bIsTestModeActive == true )
		{
			EnforcementManageComponent->SetupCharacters(DevSetting->TestPlayableCharacterIDs);	
		}
	}
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

bool AMUGameMode::IsStageCleared(FName StageID)
{
	if ( IsValid(StageManagingComponent) == false )
    {
    	return false;
    }

	return StageManagingComponent->IsStageCleared( StageID );
}

bool AMUGameMode::IsStageActiveOrCleared(FName StageID)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return false;
	}

	return StageManagingComponent->IsStageActiveOrCleared( StageID );
}

void AMUGameMode::RegisterStageSpawner(FName SpawnerID)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return;
	}

	StageManagingComponent->RegisterStageSpawner( SpawnerID );
}

void AMUGameMode::UnregisterStageSpawner(FName SpawnerID)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return;
	}

	StageManagingComponent->UnregisterStageSpawner( SpawnerID );
}

FOnStageEvents& AMUGameMode::GetStageEvents()
{
	return StageManagingComponent->GetStageEvents();
}

void AMUGameMode::StartStage(FName StageID)
{
	if ( IsValid(StageManagingComponent) == false )
	{
		return;
	}

	StageManagingComponent->StartStage( StageID );
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
    
	//CurrentPlayer->EnforcementUnit(EnforcementID);
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

	//CurrentPlayer->LevelUp();
}

AActor* AMUGameMode::GetPoolingObject(FName InSkillName, FTransform TargetTransform)
{
	return ObjectPoolingManager->GetPoolingObject(InSkillName, TargetTransform);
}
