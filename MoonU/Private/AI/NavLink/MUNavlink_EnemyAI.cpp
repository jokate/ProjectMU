// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NavLink/MUNavlink_EnemyAI.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


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
	ACharacter* Character = Cast<ACharacter>(MovingActor);

	if (Character == nullptr)
	{
		return;
	}
	
	FVector OutVector;
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, OutVector, Character->GetActorLocation(), DestinationPoint);

	Character->LaunchCharacter(OutVector, true, true);
}

