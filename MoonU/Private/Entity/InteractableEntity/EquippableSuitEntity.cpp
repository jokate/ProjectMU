// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/EquippableSuitEntity.h"

#include "Data/MUGameSettings.h"
#include "Interface/SuitEquipper.h"
#include "Library/MUFunctionLibrary.h"


// Sets default values
AEquippableSuitEntity::AEquippableSuitEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AEquippableSuitEntity::OnInteracted(AActor* InstigatorActor)
{
	auto* SuitEquipper = Cast<ISuitEquipper>(InstigatorActor);

	if (SuitEquipper == nullptr)
	{
		return;
	}

	SuitEquipper->SetSuitEquipped(true);
}

