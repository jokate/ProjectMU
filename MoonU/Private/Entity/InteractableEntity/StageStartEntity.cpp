// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/StageStartEntity.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/StageManager.h"


// Sets default values
AStageStartEntity::AStageStartEntity()
{
	bRemainAfterInteraction = true;
}

// Called when the game starts or when spawned
void AStageStartEntity::BeginPlay()
{
	Super::BeginPlay();
}

void AStageStartEntity::OnInteracted(AActor* InstigatorActor)
{
	Super::OnInteracted(InstigatorActor);

	UWorld* World = GetWorld();

	if ( IsValid( World ) == false )
	{
		return;		
	}
	
	AGameModeBase* GM = World->GetAuthGameMode();

	if ( IsValid( GM ) == false)
	{
		return;
	}

	IStageManager* StageManager = Cast<IStageManager>(GM);

	if ( StageManager == nullptr )
    {
    	return;
    }

	StageManager->StartStage( StageName );
}

const bool AStageStartEntity::IsInteractable(AActor* InstigatorActor)
{
	UWorld* World = GetWorld();

	if ( IsValid( World ) == false )
	{
		return false;		
	}
	
	AGameModeBase* GM = World->GetAuthGameMode();

	if ( IsValid( GM ) == false)
	{
		return false;
	}

	IStageManager* StageManager = Cast<IStageManager>(GM);

	if ( StageManager == nullptr )
	{
		return false;
	}
	
	bool Interactable = Super::IsInteractable(InstigatorActor);
	Interactable &= StageManager->IsStageCleared(StageName);

	return Interactable;
}


