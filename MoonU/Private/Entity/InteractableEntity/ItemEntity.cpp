// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/InteractableEntity/ItemEntity.h"


// Sets default values
AItemEntity::AItemEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AItemEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

