// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/BoxEntity/StageDrivenBoxEntity.h"

#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/StageManager.h"


// Sets default values
AStageDrivenBoxEntity::AStageDrivenBoxEntity()
{
}

void AStageDrivenBoxEntity::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for ( const FDataDrivenBox& BoxData : BoundaryBoxes )
	{
		FTransform NewTransform = GetActorTransform() * BoxData.BoxTransform;
		UActorComponent* CreatedComp = AddComponentByClass(UBoxComponent::StaticClass(), false, FTransform(), false );

		if ( IsValid( CreatedComp ) == false )
		{
			continue;
		}

		UBoxComponent* BoxComp = Cast<UBoxComponent>(CreatedComp);

		if ( IsValid( BoxComp ) == false )
		{
			continue;
		}

		BoxComp->SetBoxExtent(BoxData.BoxExtent);
		BoxComp->SetWorldTransform(NewTransform);
		BoxComp->SetCollisionProfileName(TEXT("NoCollision"));
		BoxComp->SetHiddenInGame( false );
		BoundaryBoxComponents.Add( BoxComp );
	}
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
	StageEvents.OnStageCleared.AddDynamic( this , &AStageDrivenBoxEntity::OnClearStage);
}

void AStageDrivenBoxEntity::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

	FOnStageEvents& StageEvents = StageManager->GetStageEvents();

	StageEvents.OnStageStarted.RemoveAll( this );
	StageEvents.OnStageCleared.RemoveAll( this );
	
	for ( UBoxComponent* BoundaryBox : BoundaryBoxComponents )
	{
		if ( IsValid( BoundaryBox ) == false)
		{
			continue;
		}
		
		BoundaryBox->DestroyComponent();	
	}

	BoundaryBoxComponents.Empty();
	
	Super::EndPlay(EndPlayReason);
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

	for ( UBoxComponent* BoundaryBox : BoundaryBoxComponents )
	{
		if ( IsValid(BoundaryBox ) == true )
		{
			BoundaryBox->SetCollisionProfileName(TEXT("StageCollision"));
		}
	}

}

void AStageDrivenBoxEntity::OnClearStage(FName ClearedStage)
{
	for ( UBoxComponent* BoundaryBox : BoundaryBoxComponents )
	{
		if ( IsValid(BoundaryBox ) == true )
		{
			BoundaryBox->SetCollisionProfileName(TEXT("NoCollision"));
		}
	}
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
