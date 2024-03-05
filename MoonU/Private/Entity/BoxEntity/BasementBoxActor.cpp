// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/BoxEntity/BasementBoxActor.h"

#include "Interface/SpaceTraveler.h"


// Sets default values

ABasementBoxActor::ABasementBoxActor()
{
	BasementMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BasementMesh");
}

void ABasementBoxActor::OnBoxInBound()
{
	Super::OnBoxInBound();

	if (CachedLocalPlayerCharacter == nullptr)
	{
		return;
	}

	if (auto* SpaceTraveler = Cast<ISpaceTraveler>(CachedLocalPlayerCharacter))
	{
		SpaceTraveler->OnCharacterInBasement();
	}
}

void ABasementBoxActor::OnBoxOutBound()
{
	Super::OnBoxOutBound();
	
	if (CachedLocalPlayerCharacter == nullptr)
	{
		return;
	}

	if (auto* SpaceTraveler = Cast<ISpaceTraveler>(CachedLocalPlayerCharacter))
	{
		SpaceTraveler->OnCharacterOutBasement();
	}
}
