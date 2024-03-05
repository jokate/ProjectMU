// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/InteractableEntity.h"


// Sets default values
AInteractableEntity::AInteractableEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	InteractableStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("InteractableMeshComponent");
}

// Called when the game starts or when spawned
void AInteractableEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

const FGameplayTag& AInteractableEntity::GetEntityTag()
{
	return EntityTag;
}

void AInteractableEntity::OnInteracted(AActor* InstigatorActor)
{
	if (bRemainAfterInteraction == false)
	{
		Destroy();	
	}
}

