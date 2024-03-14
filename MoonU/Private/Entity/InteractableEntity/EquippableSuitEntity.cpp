// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/EquippableSuitEntity.h"

#include "Components/MUSuitComponent.h"
#include "Data/MUGameSettings.h"
#include "Interface/SuitEquipper.h"
#include "Library/MUFunctionLibrary.h"


// Sets default values
AEquippableSuitEntity::AEquippableSuitEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SuitComponent = CreateDefaultSubobject<UMUSuitComponent>("SuitComponent");
}

void AEquippableSuitEntity::BeginPlay()
{
	Super::BeginPlay();

	AActor* SuitActor = GetWorld()->SpawnActor(SuitActorClass);
	if (SuitActor == nullptr)
	{
		return;
	}
	
	SuitComponent->EquipSuit(SuitActor);
}

const bool AEquippableSuitEntity::IsInteractable(AActor* InstigatorActor)
{
	return true;
}


void AEquippableSuitEntity::OnInteracted(AActor* InstigatorActor)
{
	auto* SuitEquipper = Cast<ISuitEquipper>(InstigatorActor);

	if (SuitEquipper == nullptr)
	{
		return;
	}

	const bool bIsSuitEquipped = SuitEquipper->GetSuitEquipped();

	if (bIsSuitEquipped)
	{
		AActor* SuitActor = SuitEquipper->UnEquipSuit();

		if (SuitActor == nullptr)
		{
			return;
		}

		EquipSuit(SuitActor);
	}
	else
	{
		AActor* SuitActor = UnEquipSuit();

		if (SuitActor == nullptr)
		{
			return;
		}

		SuitEquipper->EquipSuit(SuitActor);
	}
}

FSuitDelegate& AEquippableSuitEntity::GetSuitEquipEvent()
{
	return SuitDelegate;
}

bool AEquippableSuitEntity::GetSuitEquipped() const
{
	return SuitComponent->GetSuitEquipped();
}

void AEquippableSuitEntity::EquipSuit(AActor* SuitEntity)
{
	auto* SuitOxygenManager = Cast<IOxygenManager>(SuitEntity);
	if (SuitOxygenManager == nullptr)
	{
		return;
	}

	SuitOxygenManager->RecoverOxygen();
	
	SuitComponent->EquipSuit(SuitEntity);
}

AActor* AEquippableSuitEntity::UnEquipSuit()
{
	return SuitComponent->UnEquipSuit();
}

