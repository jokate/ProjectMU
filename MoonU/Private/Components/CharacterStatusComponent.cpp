// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterStatusComponent.h"

#include "Data/MUGameSettings.h"
#include "Interface/Sprinter.h"
#include "Interface/UI/GameplayTagWidgetOwner.h"
#include "Interface/UI/Widget/HUDWidgetInterface.h"
#include "Blueprint/UserWidget.h"


// Sets default values for this component's properties
UCharacterStatusComponent::UCharacterStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
}

void UCharacterStatusComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(SprintTimer);
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
	Super::EndPlay(EndPlayReason);
}


void UCharacterStatusComponent::OnSprint()
{
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
	GetWorld()->GetTimerManager().SetTimer(SprintTimer, this, &UCharacterStatusComponent::UseStamina, Interval, true);
}

void UCharacterStatusComponent::OnUnsprint()
{
	GetWorld()->GetTimerManager().ClearTimer(SprintTimer);
	GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &UCharacterStatusComponent::RecoverStamina, Interval, true);
}

void UCharacterStatusComponent::UseStamina()
{
	auto* Sprinter = Cast<ISprinter>(GetOwner());
	
	if (Sprinter == nullptr)
	{
		return;
	}

	if (Sprinter->IsSprinting() == false)
	{
		return;
	}
	
	if (CurrentStamina <= 0.f)
	{
		Sprinter->OnUnsprint();
		GetWorld()->GetTimerManager().ClearTimer(SprintTimer);
		return;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina - StaminaDecreaseAmount, 0.0f, MaxStamina);
	OnUpdateStamina();
}

void UCharacterStatusComponent::RecoverStamina()
{
	if (CurrentStamina >= MaxStamina)
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
		return;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRecoverAmount, 0.0f, MaxStamina);
	OnUpdateStamina();
}

void UCharacterStatusComponent::OnUpdateStamina()
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

	auto* HUDWidgetInterface = Cast<IHUDWidgetInterface>(Widget);

	if (HUDWidgetInterface == nullptr)
	{
		return;
	}

	HUDWidgetInterface->OnStaminaChanged(CurrentStamina);
}

