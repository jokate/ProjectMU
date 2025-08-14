// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUPlayerState.h"

#include "AbilitySystemComponent.h"
#include "Attribute/MUCharacterAttributeSet.h"

AMUPlayerState::AMUPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	CharacterAttribute = CreateDefaultSubobject<UMUCharacterAttributeSet>(TEXT("ATTRIBUTE"));
}

UAbilitySystemComponent* AMUPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}