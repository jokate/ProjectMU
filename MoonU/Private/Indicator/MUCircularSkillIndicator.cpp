// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MUCircularSkillIndicator.h"

#include "NavigationSystem.h"


// Sets default values
AMUCircularSkillIndicator::AMUCircularSkillIndicator()
{
	AOEMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("AOEMeshComponent");
	RadiusComponent = CreateDefaultSubobject<UStaticMeshComponent>("RadiusComponent");
}

void AMUCircularSkillIndicator::CalculateIndicatorMesh()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if ( IsValid( PC ) == false )
	{
		return;
	}

	FVector WorldPos;
	FVector WorldDirection;
	PC->DeprojectMousePositionToWorld( WorldPos, WorldDirection );

	FVector GroundIntersection = FMath::LinePlaneIntersection(
		WorldPos,
		WorldPos + WorldDirection * 10000.0f,  // 충분히 먼 점
		FVector(0, 0, 0),                      // 지면 상의 한 점
		FVector::UpVector                      // 지면의 법선 (Z축)
	);

	APawn* OwnerPawn = PC->GetPawn();

	if ( IsValid( OwnerPawn ) == false )
	{
		return;
	}

	FVector DirectionVector = GroundIntersection - OwnerPawn->GetActorLocation();
	GroundIntersection = OwnerPawn->GetActorLocation() + DirectionVector.GetClampedToMaxSize( MaxAttackDistance );
	GroundIntersection.Z = 0.f;
	
	DrawDebugSphere( GetWorld(), GroundIntersection, 50, 50, FColor::Blue);

	FNavLocation ProjectedLocation;
	FVector ProjectExtent =  FVector::One() * 10000.f;

	UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	if ( IsValid( NavSystem ) == false )
	{
		return;
	}
	
	if ( NavSystem->ProjectPointToNavigation(GroundIntersection,
		ProjectedLocation, ProjectExtent ) == false )
	{
		UE_LOG(LogTemp, Error, TEXT("Project Failed"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Location : %s"), *ProjectedLocation.Location.ToString())

	TargetLocation = GroundIntersection;
	
	DrawDebugSphere( GetWorld(), ProjectedLocation, AOERadius, AOERadius, FColor::Red);
}

