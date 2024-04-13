﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterBase.h"

#include "MotionWarpingComponent.h"
#include "Components/AbilityInitComponent.h"
#include "Components/TimeWindComponent.h"


// Sets default values
AMUCharacterBase::AMUCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimeWindComponent = CreateDefaultSubobject<UTimeWindComponent>(TEXT("TimeWinder"));
	AbilityInitComponent = CreateDefaultSubobject<UAbilityInitComponent>(TEXT("AbilityInitComponent"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpComponent"));
}

// Called when the game starts or when spawned
void AMUCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	TimeWindComponent->OnIntialize();
}

void AMUCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

UAbilitySystemComponent* AMUCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMUCharacterBase::SetTimeWind(bool InTimeRewind)
{
	TimeWindComponent->SetTimeWind(InTimeRewind);
}

const bool AMUCharacterBase::GetTimeWind()
{
	return TimeWindComponent->GetTimeWind();
}

UMotionWarpingComponent* AMUCharacterBase::GetMotionWarpComponent()
{
	return MotionWarpingComponent;
}

void AMUCharacterBase::SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue)
{
	
}

void AMUCharacterBase::ReleaseMotionWarp(const FName InName)
{
	MotionWarpingComponent->RemoveWarpTarget(InName);
}

