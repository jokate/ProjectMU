// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TargetManagingComponent.h"


// Sets default values for this component's properties
UTargetManagingComponent::UTargetManagingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTargetManagingComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UTargetManagingComponent::IsTargetValid() const
{
	return IsValid(TargetActor);
}

void UTargetManagingComponent::SetupTarget(AActor* NewTarget)
{
	if (IsValid(NewTarget) == false)
	{
		return;
	}
	
	if ( TargetActor != NewTarget)
	{
		ResetTarget();
		
		//Target에 대한 부분을 세팅하는 과정이 있어야 한다.
		ActivationType = ETargetActivationType::Actor;
		TargetActor = NewTarget;
	}
}

void UTargetManagingComponent::SetupTargetLocation(FVector NewTargetLocation)
{
	if (ActivationType > ETargetActivationType::Location)
	{
		return;
	}

	if ( TargetLocation != NewTargetLocation )
	{
		ResetTarget();
		ActivationType = ETargetActivationType::Location;
		TargetLocation = NewTargetLocation;
	}
}

void UTargetManagingComponent::ResetTarget()
{
	ActivationType = ETargetActivationType::NoTarget;
	TargetLocation = FVector::ZeroVector;
	TargetActor = nullptr;
}
