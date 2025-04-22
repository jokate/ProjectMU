// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MUSkillIndicator.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"


// Sets default values
AMUSkillIndicator::AMUSkillIndicator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IndicatorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("IndicatorMeshComponent");
	IndicatorDecalComponent = CreateDefaultSubobject<UDecalComponent>("IndicatorDecalComponent");
}

// Called when the game starts or when spawned
void AMUSkillIndicator::BeginPlay()
{
	Super::BeginPlay();
	
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

