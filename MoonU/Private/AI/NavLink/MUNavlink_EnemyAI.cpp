// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NavLink/MUNavlink_EnemyAI.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Data/MUStruct.h"
#include "Utility/VectorWrapper.h"


// Sets default values
AMUNavlink_EnemyAI::AMUNavlink_EnemyAI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bSmartLinkIsRelevant = true;
}

// Called when the game starts or when spawned
void AMUNavlink_EnemyAI::BeginPlay()
{
	Super::BeginPlay();
	OnSmartLinkReached.AddDynamic(this, &AMUNavlink_EnemyAI::OnAIReachedToPoint);
}

void AMUNavlink_EnemyAI::OnAIReachedToPoint(AActor* MovingActor, const FVector& DestinationPoint)
{
	FGameplayEventData EventData;

	UVectorWrapper* VectorWrapper = NewObject<UVectorWrapper>();
	VectorWrapper->SetVector(DestinationPoint);
	EventData.OptionalObject = VectorWrapper;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MovingActor, EventSendTag, EventData);
}

