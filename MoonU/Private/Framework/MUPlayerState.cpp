// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MUPlayerState.h"

#include "Character/MUCharacterPlayer.h"
#include "AbilitySystemComponent.h"

AMUPlayerState::AMUPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* AMUPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}