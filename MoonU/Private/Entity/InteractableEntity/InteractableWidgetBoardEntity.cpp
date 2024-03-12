// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/InteractableWidgetBoardEntity.h"

#include "Data/MUGameSettings.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "Interface/UI/Widget/MUWidgetInterface.h"


// Sets default values
AInteractableWidgetBoardEntity::AInteractableWidgetBoardEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInteractableWidgetBoardEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableWidgetBoardEntity::OnInteracted(AActor* InstigatorActor)
{
	auto* GameplayTagOwner = Cast<IGameplayTagWidgetOwner>(InstigatorActor);
	
	if (GameplayTagOwner == nullptr)
	{
		return;	
	}

	const auto* GS = UMUGameSettings::Get();
	if (GS == nullptr)
	{
		return;
	}
	
	GameplayTagOwner->ShowWidgetByGameplayTag(UIGameplayTag);
	UUserWidget* Widget = GameplayTagOwner->GetWidgetByGameplayTag(UIGameplayTag);

	if (Widget == nullptr)
	{
		return;
	}

	if (auto* MUWidget = Cast<IMUWidgetInterface>(Widget))
	{
		MUWidget->OnWidgetUpdatedByActor(this);
	}
}


