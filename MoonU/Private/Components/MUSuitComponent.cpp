// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MUSuitComponent.h"

#include "Data/MUGameSettings.h"
#include "Interface/SuitEquipper.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "Blueprint/UserWidget.h"
#include "Interface/UI/Widget/MUWidgetInterface.h"

// Sets default values for this component's properties
UMUSuitComponent::UMUSuitComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMUSuitComponent::SetSuitEquipped(bool InEquipped)
{
	AActor* OwnerActor = GetOwner();

	if (!IsValid(OwnerActor))
	{
		return;
	}

	if (auto* SuitEquipper = Cast<ISuitEquipper>(OwnerActor))
	{
		bSuitEquipped = InEquipped;

		const FSuitDelegate& HeadEvent = SuitEquipper->GetSuitEquipEvent();

		if (HeadEvent.IsBound())
		{
			HeadEvent.Execute(bSuitEquipped);
		}
	}
}

void UMUSuitComponent::SetHeadEquipped(bool InEquipped)
{
	AActor* OwnerActor = GetOwner();

	if (!IsValid(OwnerActor))
	{
		return;
	}

	if (auto* SuitEquipper = Cast<ISuitEquipper>(OwnerActor))
	{
		bHeadEquipped = InEquipped;

		const FSuitDelegate& HeadEvent = SuitEquipper->GetHeadEquipEvent();

		if (HeadEvent.IsBound())
		{
			HeadEvent.Execute(bHeadEquipped);
		}
	}
}

bool UMUSuitComponent::GetSuitEquipped() const
{
	return bSuitEquipped;
}

bool UMUSuitComponent::GetHeadEquipped() const
{
	return bHeadEquipped;
}


// Called when the game starts
void UMUSuitComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentOxygenAmount = MaxOxygenAmount;
}

void UMUSuitComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
	
	Super::EndPlay(EndPlayReason);
}

void UMUSuitComponent::UseOxygen()
{
	if (CurrentOxygenAmount <= 0.f)
	{
		return;
	}

	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount - OxygenUseAmount, 0.0f, MaxOxygenAmount);
	OnUpdateOxygen();
}

void UMUSuitComponent::RecoverOxygen()
{
	if (CurrentOxygenAmount >= MaxOxygenAmount)
	{
		return;
	}

	CurrentOxygenAmount = FMath::Clamp(CurrentOxygenAmount + OxygenRecoverAmount, 0.0f, MaxOxygenAmount);
	OnUpdateOxygen();
}

void UMUSuitComponent::OnUpdateOxygen()
{
	AActor* OwnerActor = GetOwner();

	if (OwnerActor == nullptr)
	{
		return;
	}

	auto* GameplayTagWidgetOwner = Cast<IGameplayTagWidgetOwner>(OwnerActor);

	if (GameplayTagWidgetOwner == nullptr)
	{
		return;
	}
	const auto* GS = UMUGameSettings::Get();

	if (GS == nullptr)
	{
		return;
	}
	
	UUserWidget* Widget = GameplayTagWidgetOwner->GetWidgetByGameplayTag(GS->HUDGameplayTag);

	if (Widget == nullptr)
	{
		return;
	}

	auto* HUDWidgetInterface = Cast<IMUWidgetInterface>(Widget);

	if (HUDWidgetInterface == nullptr)
	{
		return;
	}

	HUDWidgetInterface->OnWidgetUpdated();
}

void UMUSuitComponent::OnCharacterInBasement()
{
	GetWorld()->GetTimerManager().ClearTimer(OxygenTimerHandle);
	
	if (!RecoverTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimerHandle, this, &UMUSuitComponent::RecoverOxygen, TimerInterval, true);
	}
}

void UMUSuitComponent::OnCharacterOutBasement()
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
	
	if (!OxygenTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(OxygenTimerHandle, this, &UMUSuitComponent::UseOxygen, TimerInterval, true);
	}
}


