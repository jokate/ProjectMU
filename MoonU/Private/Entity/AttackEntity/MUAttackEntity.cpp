// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/MUAttackEntity.h"
#include "Character/MUCharacterBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMUAttackEntity::AMUAttackEntity()
{
}

// Called when the game starts or when spawned
void AMUAttackEntity::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer( ReactCheckTimer, this, &AMUAttackEntity::DoAttack, ReactCheckInterval, true );
}

void AMUAttackEntity::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer( ReactCheckTimer );
	ReactedActors.Empty();
	Super::EndPlay(EndPlayReason);
}

void AMUAttackEntity::DoAttack()
{
	TArray<AActor*> Characters = GetAttackableActorList();
	for ( AActor* Character : Characters )
	{
		if ( IsValid(Character) == false)
		{
			continue;
		}
		
		if ( CheckReact(Character) == true )
		{
			OnReacted(Character);
		}	
	}
}

TArray<AActor*> AMUAttackEntity::GetAttackableActorList()
{
	return TArray<AActor*>();
}

void AMUAttackEntity::ReturnToPooling()
{
	SetActorHiddenInGame( false );
	SetActorTickEnabled( true );
	
	// 타이머 비할성화 조치.
	GetWorldTimerManager().ClearTimer( ReactCheckTimer );
	ReactedActors.Empty();

	bIsActive = false;
}

bool AMUAttackEntity::CanActivateObject()
{
	// 비활성화 된 경우에 한해서는 작동.
	return !bIsActive;
}

void AMUAttackEntity::ActivateObject(FTransform Transform)
{
	SetActorHiddenInGame( false );
	SetActorTickEnabled( true );
	SetActorTransform( Transform );

	bIsActive = true;
	
	GetWorldTimerManager().SetTimer( ReactCheckTimer, this, &AMUAttackEntity::DoAttack, ReactCheckInterval, true );
}

void AMUAttackEntity::RegisterOwner(AActor* InSpawnedOwwner)
{
	SpawnedOwner = InSpawnedOwwner;
}

void AMUAttackEntity::OnReacted(AActor* ReactedActor)
{
	if ( bHitOnce == true)
	{
		ReactedActors.Add(ReactedActor);
	}
}

bool AMUAttackEntity::CheckReact(AActor* ReactTarget) const
{
	if ( bHitOnce == true && ReactedActors.Contains(ReactTarget) == true )
	{
		return false;
	}
	
	IGenericTeamAgentInterface* OwnerTeam = Cast<IGenericTeamAgentInterface>( SpawnedOwner );

	if ( OwnerTeam == nullptr )
	{
		return false;
	}

	ETeamAttitude::Type Attitude = OwnerTeam->GetTeamAttitudeTowards( *ReactTarget );

	if (AttackTo == EAttackingType::ENEMY)
	{
		return Attitude == ETeamAttitude::Hostile;
	}

	if ( AttackTo == EAttackingType::FRIENDLY)
	{
		return Attitude == ETeamAttitude::Friendly;
	}

	return true;
}

