// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MUObjectPoolingManager.h"

#include "Data/MUDataPrimaryAsset.h"
#include "Data/DataTable/MUData.h"
#include "Entity/AttackEntity/MUAttackEntity.h"
#include "Interface/ObjectPoolingTarget.h"
#include "Library/MUFunctionLibrary.h"


// Sets default values for this component's properties
UMUObjectPoolingManager::UMUObjectPoolingManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

AActor* UMUObjectPoolingManager::GetPoolingObject(FName InSkillName, FTransform TargetTransform )
{
	UMUDataPrimaryAsset* DataPrimaryAsset = UMUFunctionLibrary::GetDataPrimaryAsset(this);

	if ( IsValid(DataPrimaryAsset) == false )
	{
		return nullptr;
	}
	
	FMUAttackEntityData AttackEntityData;
	if ( UMUFunctionLibrary::GetRegistryData<FMUAttackEntityData>(this, DataPrimaryAsset->AttackEntityRegistryType, InSkillName, AttackEntityData) == false )
	{
		return nullptr;
	}
	
	if ( PoolingMap.Contains(InSkillName) == false )
	{
		FObjectPoolInfo PoolingInfo;
		PoolingInfo.PoolingMaxCount = AttackEntityData.MaxPoolingCount;
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(AttackEntityData.AttackEntityClass, TargetTransform );
		PoolingInfo.PoolingObjects.Add( SpawnActor );
		PoolingMap.Add(InSkillName, PoolingInfo);
	}
	
	FObjectPoolInfo* TempObjectInfo = PoolingMap.Find(InSkillName);

	if ( TempObjectInfo == nullptr )
	{
		return nullptr;
	}

	TArray<AActor*>& TempPoolingObjects = TempObjectInfo->PoolingObjects;
	for ( int32 Index = 0; Index < TempObjectInfo->PoolingMaxCount; Index++ )
	{
		bool bValidIndex = TempPoolingObjects.IsValidIndex(Index);

		// 사용 가능하면 즉시 ㄱㄱ
		if ( bValidIndex == true )
		{
			AActor* TempPoolingObject = TempPoolingObjects[Index];

			if ( IsValid( TempPoolingObject ) == false )
			{
				continue;
			}
			
			IObjectPoolingTarget* PoolingTarget = Cast<IObjectPoolingTarget>(TempPoolingObject);

			if ( PoolingTarget == nullptr )
			{
				continue;
			}

			if ( PoolingTarget->CanActivateObject() == false )
			{
				continue;
			}
			
			return TempPoolingObject;
		}

		// 아닌 경우에는 즉시 생성.
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(AttackEntityData.AttackEntityClass, TargetTransform );
		TempPoolingObjects.Add(SpawnActor);
		return SpawnActor;
	}

	return nullptr;
}


