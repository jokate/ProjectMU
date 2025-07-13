// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterPatroller.h"

#include "AI/MUAIDefines.h"
#include "Components/SplineComponent.h"


// Sets default values
AMUCharacterPatroller::AMUCharacterPatroller(const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("Patrol");
}

void AMUCharacterPatroller::IncrementPatrolRoute()
{
	const int32 PatrolStartIndex = 0;
	
	PatrolIndex += PatrolDirection;

	if (PatrolIndex == SplineComponent->GetNumberOfSplinePoints() - 1)
	{
		PatrolDirection = MU_PATROL_BACK;
	}
	else if (PatrolIndex == PatrolStartIndex)
	{
		PatrolDirection = MU_PATROL_FRONT;
	}
}

const FVector AMUCharacterPatroller::GetPositionForSpline()
{
	return SplineComponent->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::World);
}

