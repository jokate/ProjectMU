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
	CurrentOxygenAmount = MaxOxygenAmount;
}

void UOxygenManageComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void UOxygenManageComponent::OnUseOxygen()
{
	if (CurrentOxygenAmount <= 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
		return;
	}

	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount - OxygenUseAmount, 0.0f, MaxOxygenAmount);

	if (OxygenUpdateDelegate.IsBound())
    {
    	OxygenUpdateDelegate.Execute();
    }
}

void UOxygenManageComponent::OnRecoverOxygen()
{
	if (CurrentOxygenAmount >= MaxOxygenAmount)
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
		return;
	}

	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount + OxygenRecoverAmount, 0.0f, MaxOxygenAmount);

	if (OxygenUpdateDelegate.IsBound())
	{
		OxygenUpdateDelegate.Execute();
	}
}

void UOxygenManageComponent::UseOxygen()
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
	if (OxygenTimerHandle.IsValid() == false)
	{
		GetWorld()->GetTimerManager().SetTimer(OxygenTimerHandle, this, &UOxygenManageComponent::OnUseOxygen, TimerInterval, true);
	}
}

void UOxygenManageComponent::RecoverOxygen()
{
	GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
	if (RecoverTimerHandle.IsValid() == false)
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimerHandle, this, &UOxygenManageComponent::OnRecoverOxygen, TimerInterval, true);
	}
}

void UOxygenManageComponent::RecoverOxygen(const float InOxygen)
{
	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount + InOxygen, 0.0f, MaxOxygenAmount);
}

FOxygenUpdateDelegate& UOxygenManageComponent::GetOxygenUpdateDelegate()
{
	return OxygenUpdateDelegate;
}

void UOxygenManageComponent::SetMaxOxygenAmount(float InNewMaxOxygenAmount)
{
	MaxOxygenAmount = InNewMaxOxygenAmount;
}

