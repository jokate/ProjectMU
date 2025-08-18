// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/AttackEntity/MUProjectileEntity.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AMUProjectileEntity::AMUProjectileEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}

// Called when the game starts or when spawned
void AMUProjectileEntity::BeginPlay()
{
	Super::BeginPlay();
}

TArray<AActor*> AMUProjectileEntity::GetAttackableActorList()
{
	
	return Super::GetAttackableActorList();
}
