// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterNonPlayer.h"

#include "AbilitySystemComponent.h"
#include "MUDefines.h"
#include "Attribute/MUCharacterAttributeSetBase.h"
#include "Components/AbilityInitComponent.h"
#include "Components/TimeWindComponent.h"


// Sets default values
AMUCharacterNonPlayer::AMUCharacterNonPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UMUCharacterAttributeSetBase>(TEXT("CharacterAttribute"));
}

void AMUCharacterNonPlayer::OnDead(const FGameplayEventData* Data)
{
}


UAbilitySystemComponent* AMUCharacterNonPlayer::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMUCharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMUCharacterNonPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ASC->InitAbilityActorInfo(this, this);
	ASC->GenericGameplayEventCallbacks.FindOrAdd(MU_CHARACTERSTATE_DEAD).AddUObject(this, &AMUCharacterNonPlayer::OnDead);

	AbilityInitComponent->InitAbilities();
}
