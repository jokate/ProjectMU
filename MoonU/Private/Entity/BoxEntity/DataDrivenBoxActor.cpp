// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/BoxEntity/DataDrivenBoxActor.h"
#include "GameFramework/Character.h"
#include "Library/MUFunctionLibrary.h"


// Sets default values
ADataDrivenBoxActor::ADataDrivenBoxActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ADataDrivenBoxActor::SettingUpInformation()
{
	GetWorld()->GetTimerManager().SetTimer(CheckTimerHandle, this, &ADataDrivenBoxActor::CharacterBoundCheckLoop, TimerInterval, true);
	CachedLocalPlayerCharacter = UMUFunctionLibrary::GetLocalPlayerCharacter(this);
}

// Called when the game starts or when spawned
void ADataDrivenBoxActor::BeginPlay()
{
	Super::BeginPlay();

	SettingUpInformation();
}

void ADataDrivenBoxActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if ( CheckTimerHandle.IsValid() == true )
	{
		GetWorld()->GetTimerManager().ClearTimer(CheckTimerHandle);	
	}
	
	Super::EndPlay(EndPlayReason);
}

void ADataDrivenBoxActor::CharacterBoundCheckLoop()
{
	if (CachedLocalPlayerCharacter == nullptr)
	{
		//캐싱된 플레이어가 없는 경우 재`캐싱을 한다.
		CachedLocalPlayerCharacter = UMUFunctionLibrary::GetLocalPlayerCharacter(this);
		return;
	}

	bool bIsInBound = false;

	for (const FDataDrivenBox& DrivenBox : DataDrivenBoxes)
	{
		if (CheckCharacterInBound(DrivenBox))
		{
			bIsInBound = true;
		}
	}

	if (bIsInBound)
	{
		OnBoxInBound();
	}
	else
	{
		OnBoxOutBound();
	}
}

bool ADataDrivenBoxActor::CheckCharacterInBound(const FDataDrivenBox& DrivenBox) const
{
	const FTransform BoxTransform = DrivenBox.BoxTransform;
	const FVector BoundBoxExtent = DrivenBox.BoxExtent;

	const FVector ActorLocation = CachedLocalPlayerCharacter->GetActorLocation();
	const FVector LocalSpaceLocation = BoxTransform.InverseTransformPosition(ActorLocation);


	const float MaxZ = BoundBoxExtent.Z;
	const float MinZ = -BoundBoxExtent.Z;
	const float MaxX = BoundBoxExtent.X;
	const float MinX = -BoundBoxExtent.X;
	const float MaxY = BoundBoxExtent.Y;
	const float MinY = -BoundBoxExtent.Y;


	const bool bContainZ = LocalSpaceLocation.Z > MinZ && LocalSpaceLocation.Z <= MaxZ;
	const bool bContainY = LocalSpaceLocation.Y > MinY && LocalSpaceLocation.Y <= MaxY;
	const bool bContainX = LocalSpaceLocation.X > MinX && LocalSpaceLocation.X <= MaxX;

	return bContainX && bContainY && bContainZ;
}

void ADataDrivenBoxActor::OnBoxInBound()
{
	
}

void ADataDrivenBoxActor::OnBoxOutBound()
{
	
}


