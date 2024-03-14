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

bool UMUSuitComponent::GetSuitEquipped() const
{
	return bSuitEquipped;
}

void UMUSuitComponent::EquipSuit(AActor* SuitEntity)
{
	AActor* OwnerActor = GetOwner();

	if (!IsValid(SuitEntity))
	{
		return;
	}
	
	if (!IsValid(OwnerActor))
	{
		return;
	}

	if (auto* SuitEquipper = Cast<ISuitEquipper>(OwnerActor))
	{
		bSuitEquipped = true;

		const FAttachmentTransformRules TransformRule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		SuitEntity->AttachToActor(GetOwner(), TransformRule);
		EquippedSuitEntity = SuitEntity;

		const FSuitDelegate& SuitEvent = SuitEquipper->GetSuitEquipEvent();

		if (SuitEvent.IsBound())
		{
			SuitEvent.Execute(bSuitEquipped);
		}
	}
}

void UMUSuitComponent::UnEquipSuit()
{
	AActor* OwnerActor = GetOwner();
	
	if (!IsValid(OwnerActor))
	{
		return;
	}

	if (auto* SuitEquipper = Cast<ISuitEquipper>(OwnerActor))
	{
		bSuitEquipped = false;

		EquippedSuitEntity = nullptr;
		
		const FSuitDelegate& SuitEvent = SuitEquipper->GetSuitEquipEvent();

		if (SuitEvent.IsBound())
		{
			SuitEvent.Execute(bSuitEquipped);
		}
	}
}

// Called when the game starts
void UMUSuitComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMUSuitComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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
	auto* SuitOxygenManager = Cast<IOxygenManager>(EquippedSuitEntity);

	if (SuitOxygenManager == nullptr)
	{
		return;
	}

	SuitOxygenManager->RecoverOxygen();
}

void UMUSuitComponent::OnCharacterOutBasement()
{
	auto* SuitOxygenManager = Cast<IOxygenManager>(EquippedSuitEntity);

	if (SuitOxygenManager == nullptr)
	{
		return;
	}

	SuitOxygenManager->UseOxygen();
}


