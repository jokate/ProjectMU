// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/EquippableSuitEntity.h"

#include "Interface/SuitEquipper.h"


// Sets default values
AEquippableSuitEntity::AEquippableSuitEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bRemainAfterInteraction = false;
}

void AEquippableSuitEntity::OnInteracted(AActor* InstigatorActor)
{
	Super::OnInteracted(InstigatorActor);
	
	auto* SuitEquipper = Cast<ISuitEquipper>(InstigatorActor);

	if (SuitEquipper == nullptr)
	{
		return;
	}

	SuitEquipper->SetSuitEquipped(true);
}

