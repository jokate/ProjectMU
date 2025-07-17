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
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(this,AMUCharacterBase::StaticClass(), Characters);

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

