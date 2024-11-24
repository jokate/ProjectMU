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

void UMULevelUpComponent::SetLevel(const int32 InLevel)
{
	// 현재 레벨에 대한 세팅.
	Level = InLevel;

	//Ability System에 대한 가정, 현재 가지고 있는 Character의 ID값을 기반으로 세팅되는 부분이 무조건적으로 필요.
	
}
