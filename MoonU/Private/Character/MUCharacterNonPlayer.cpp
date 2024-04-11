// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterNonPlayer.h"

#include "AbilitySystemComponent.h"
#include "Components/AbilityInitComponent.h"
#include "Components/TimeWindComponent.h"


// Sets default values
AMUCharacterNonPlayer::AMUCharacterNonPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AbilityInitComponent = CreateDefaultSubobject<UAbilityInitComponent>(TEXT("InitComponent"));
	TimeWindComponent = CreateDefaultSubobject<UTimeWindComponent>(TEXT("TimeWindComponent"));
}

// Called when the game starts or when spawned
void AMUCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();
	TimeWindComponent->OnIntialize();
}


UAbilitySystemComponent* AMUCharacterNonPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMUCharacterNonPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	AbilityInitComponent->InitAbilities();
}

void AMUCharacterNonPlayer::SetTimeWind(bool InTimeWind)
{
	return TimeWindComponent->SetTimeWind(InTimeWind);
}

const bool AMUCharacterNonPlayer::GetTimeWind()
{
	return TimeWindComponent->GetTimeWind();
}

