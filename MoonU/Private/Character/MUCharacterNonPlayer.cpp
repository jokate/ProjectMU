// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterNonPlayer.h"

#include "AbilitySystemComponent.h"
#include "Components/AbilityInitComponent.h"


// Sets default values
AMUCharacterNonPlayer::AMUCharacterNonPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AbilityInitComponent = CreateDefaultSubobject<UAbilityInitComponent>(TEXT("InitComponent"));
}

// Called when the game starts or when spawned
void AMUCharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

