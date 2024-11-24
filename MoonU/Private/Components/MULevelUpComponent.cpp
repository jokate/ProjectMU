// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MULevelUpComponent.h"


// Sets default values for this component's properties
UMULevelUpComponent::UMULevelUpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMULevelUpComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMULevelUpComponent::OnCharacterInitialized()
{
	if ( OnSetLevelEventCallback.IsBound() == true)
	{
		OnSetLevelEventCallback.Broadcast(Level);	
	}
}

void UMULevelUpComponent::LevelUp()
{
	SetLevel( Level + 1 );
	OnLevelUpEventCallback.Broadcast(Level);
}

