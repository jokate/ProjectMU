// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StageManagingComponent.h"

#include "ParticleHelper.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Library/MUFunctionLibrary.h"

void UStageManagingComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupStage();
}

void UStageManagingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer( SpawnCheckTimer ); 
	Super::EndPlay(EndPlayReason);
}

void UStageManagingComponent::RegisterOwnerActor(AActor* NeedToRegActor)
{
	if ( IsValid( NeedToRegActor ) == true )
	{
		OwnerActor = NeedToRegActor;
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnCheckTimer, this, &UStageManagingComponent::CheckSpawn, SpawnTimeInterval, true );
}

void UStageManagingComponent::SendClearSpawner(FName ClearedSpawnID)
{
	if ( ClearedMonsterSpawner.Contains(ClearedSpawnID) == true)
	{
		return;
	}

	ClearedMonsterSpawner.Add(ClearedSpawnID);
}

void UStageManagingComponent::SetupStage()
{
	FMUStageInfo StageInfo;
	if ( UMUFunctionLibrary::GetStageInfoData( this, StageName, StageInfo) == false )
	{
		return;
	}

	const int32 StageNum = StageInfo.StageIDs.Num();
	for ( int32 i = 0; i < StageInfo.MaxStage; ++i )
	{
		int32 RandRange = FMath::RandRange( 0, StageNum - 1 );

		FName& RandSeed = StageInfo.StageIDs[RandRange];

		if ( StagePools.Contains( RandSeed ) == true )
		{
			continue;
		}

		StagePools.Add(RandSeed);
	}
}

void UStageManagingComponent::CheckSpawn()
{
	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}
	
	FVector ActorLocation = OwnerActor->GetActorLocation();
	
	for ( const FName& TempStageName : StagePools )
	{
		FMUStageData StageData;
		if ( UMUFunctionLibrary::GetStageData( this, TempStageName, StageData )  == false )
		{
			continue;
		}
		
		float Magnitude = FVector::Distance(StageData.StreamingPos, ActorLocation);

		// 있는 경우.
		if ( StreamedLevelList.Contains(TempStageName) == true )
		{
			// 이미 스폰된 경우.
			ULevelStreamingDynamic* StreamingDynamic = StreamedLevelList[TempStageName];

			if ( IsValid(StreamingDynamic) == false)
			{
				continue;
			}
			

			if ( Magnitude > DestroyDistance )
			{
				StreamingDynamic->SetShouldBeLoaded( false );
				StreamingDynamic->SetShouldBeVisible( false );
				StreamingDynamic->SetIsRequestingUnloadAndRemoval( true );

				StreamedLevelList.Remove( TempStageName );
			}
		}
		else
		{
			// 없는 경우.
			if ( Magnitude <= SpawnDistance )
			{
				bool OutSuccess = false;
				ULevelStreamingDynamic* NewlyStreaming = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
					this, StageData.RoomLevel, StageData.StreamingPos, FRotator::ZeroRotator, OutSuccess );

				if ( OutSuccess == true )
				{
					StreamedLevelList.Add( TempStageName, NewlyStreaming );
				}
 			}
		}
	}
}

void UStageManagingComponent::StartStage(FName InStageName)
{
	// 레벨로딩 혹은 실질적인 스테이지 액터 스포닝. (몬스터 스포너나 혹은 액티베이션)
	CurrentStageName = InStageName;
	
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
