// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/MUCircularZone.h"

#include "Character/MUCharacterBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMUCircularZone::AMUCircularZone()
{
	VisualSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Visual Sphere"));
	SetRootComponent(VisualSphereComponent);

	VisualSphereComponent->SetSphereRadius(CheckRad);
}

void AMUCircularZone::OnReacted(AActor* ReactedActor)
{
	Super::OnReacted(ReactedActor);

	UE_LOG(LogTemp, Log, TEXT("Circular Reacted"));
}

bool AMUCircularZone::CheckReact(AActor* ReactTarget) const
{
	if ( Super::CheckReact(ReactTarget) == false )
	{
		return false;
	}
	
	FVector ReactLocation = ReactTarget->GetActorLocation();
	FVector ZoneLocation = GetActorLocation();

	double DistSquared = FVector::DistSquared(ReactLocation, ZoneLocation);
	double RadSquared = FMath::Square(CheckRad);
	
	return DistSquared <= RadSquared;
}

TArray<AActor*> AMUCircularZone::GetAttackableActorList()
{
	TArray<AActor*> AttackableActorList;
	UGameplayStatics::GetAllActorsOfClass(this,AMUCharacterBase::StaticClass(), AttackableActorList);
	return AttackableActorList;
}
