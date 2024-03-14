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
	return EquippedSuitEntity != nullptr;
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
		const FAttachmentTransformRules TransformRule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		SuitEntity->AttachToActor(GetOwner(), TransformRule, SuitSocket);
		EquippedSuitEntity = SuitEntity;
		
		const FSuitDelegate& SuitEvent = SuitEquipper->GetSuitEquipEvent();

		if (SuitEvent.IsBound())
		{
			SuitEvent.Execute(true);
		}
	}
}

AActor* UMUSuitComponent::UnEquipSuit()
{
	AActor* OwnerActor = GetOwner();
	
	if (!IsValid(OwnerActor))
	{
		return nullptr;
	}

	AActor* ReturnActor = nullptr;
	if (auto* SuitEquipper = Cast<ISuitEquipper>(OwnerActor))
	{
		ReturnActor = EquippedSuitEntity;
		const FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative,EDetachmentRule::KeepRelative, false);
		EquippedSuitEntity->DetachFromActor(DetachmentTransformRules);
		EquippedSuitEntity = nullptr;
		
		const FSuitDelegate& SuitEvent = SuitEquipper->GetSuitEquipEvent();

		if (SuitEvent.IsBound())
		{
			SuitEvent.Execute(false);
		}
	}

	return ReturnActor;
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
