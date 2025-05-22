// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MUSkillIndicator.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"


// Sets default values
AMUSkillIndicator::AMUSkillIndicator()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AMUSkillIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateIndicatorMesh();
}

void AMUSkillIndicator::CalculateIndicatorMesh()
{
}

void AMUSkillIndicator::SetupIndicatorInfo(APlayerController* OwnerController, float AttackDistance, float InAOERadius )
{
	if ( IsValid( OwnerController ) == true )
	{
		OwnerPlayerController = OwnerController;	
	}

	MaxAttackDistance = AttackDistance;
	AOERadius = InAOERadius;
}

