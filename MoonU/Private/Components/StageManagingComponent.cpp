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

bool UStageManagingComponent::IsStageCleared(FName StageID)
{
	return ClearedMonsterSpawner.Contains(StageID);
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
		
		FVector2D RandPos = FVector2D::ZeroVector;
		
		while ( true )
		{
			RandPos = FVector2D( FMath::RandRange(-WorldRand.X, WorldRand.X), FMath::RandRange(-WorldRand.Y, WorldRand.Y) );
			
			if ( CheckIsValidPosition( RandPos ) == true )
			{
				UE_LOG(LogTemp, Log, TEXT("RandPos Complete %s, %s"), *RandPos.ToString(), *RandSeed.ToString() );
				break;
			}		
		}

		FStagePoolingData StagePoolData(RandSeed, RandPos);
		
		StagePools.Add(StagePoolData);
	}
}

void UStageManagingComponent::CheckSpawn()
{
	if ( IsValid( OwnerActor ) == false )
	{
		return;
	}
	
	FVector ActorLocation = OwnerActor->GetActorLocation();

	FVector2D ActorPos ( ActorLocation.X, ActorLocation.Y );
	
	for ( const FStagePoolingData& TempStagePool : StagePools )
	{
		const FName& TempStageName = TempStagePool.StageName;
		const FVector2D& TempStageLocation = TempStagePool.SpawnLocation;
		FMUStageData StageData;
		if ( UMUFunctionLibrary::GetStageData( this, TempStageName, StageData )  == false )
		{
			continue;
		}
		float Magnitude = FVector2D::Distance(TempStageLocation, ActorPos );
		
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
				FHitResult HitResult;
				
				GetWorld()->LineTraceSingleByChannel(HitResult, FVector(TempStageLocation.X, TempStageLocation.Y, -StageSpawnHeight),
					FVector(TempStageLocation.X, TempStageLocation.Y, StageSpawnHeight), ECC_Visibility);

				UE_LOG(LogTemp, Log, TEXT("Stage Spawn Location %s"), *HitResult.Location.ToString())
				
				bool OutSuccess = false;
				ULevelStreamingDynamic* NewlyStreaming = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(
					this, StageData.RoomLevel, HitResult.Location, FRotator::ZeroRotator, OutSuccess );

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

	const FOnStageStarted& StageStarted = StageEvents.OnStageStarted;
	
	if ( StageStarted.IsBound() == true )
	{
		StageStarted.Broadcast(CurrentStageName);
	}
}

void UStageManagingComponent::EndStage()
{
	const FOnStageCleared& ClearedEvent = StageEvents.OnStageCleared;
	
	if ( ClearedEvent.IsBound() == true )
	{
		ClearedEvent.Broadcast( CurrentStageName );
	}

	ClearedStage.Add(CurrentStageName);
	
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

void UStageManagingComponent::UnregisterStageSpawner(FName SpawnerID)
{
	ActiveStageSpawners.Remove(SpawnerID);

	if ( ActiveStageSpawners.Num() <= 0 )
	{
		EndStage();
	} 
}

bool UStageManagingComponent::CheckIsValidPosition(FVector2D RandPos)
{
	bool RetVal = true;
	for ( FStagePoolingData& StagePool : StagePools )
	{
		FVector2D StagePoolLocation = StagePool.SpawnLocation;

		// 현재 풀링된 정보와 대조.
		float SquaredDist = FMath::Square( FVector2D::Distance( RandPos, StagePoolLocation ) );

		// 체킹 레인지.
		float SquaredRange = FMath::Square( StageSpawnCheckDistance );

		// 만약 가깝다면?
		if ( SquaredDist <= SquaredRange )
		{
			RetVal = false;
			break;
		}
	}

	return RetVal;
}

