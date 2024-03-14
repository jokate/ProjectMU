// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/OxygenManageComponent.h"


UOxygenManageComponent::UOxygenManageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOxygenManageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UOxygenManageComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void UOxygenManageComponent::UseOxygen()
{
	if (CurrentOxygenAmount <= 0.f)
	{
		return;
	}

	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount - OxygenUseAmount, 0.0f, MaxOxygenAmount);
}

void UOxygenManageComponent::RecoverOxygen()
{
	if (CurrentOxygenAmount >= MaxOxygenAmount)
	{
		return;
	}

	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount + OxygenRecoverAmount, 0.0f, MaxOxygenAmount);
}

void UOxygenManageComponent::RecoverOxygen(const float InOxygen)
{
	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount + InOxygen, 0.0f, MaxOxygenAmount);
}

