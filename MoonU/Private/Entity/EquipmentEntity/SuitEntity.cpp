﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/EquipmentEntity/SuitEntity.h"

#include "Components/OxygenManageComponent.h"


// Sets default values
ASuitEntity::ASuitEntity()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(SuitSkeletalComponent);
	SuitSkeletalComponent = CreateDefaultSubobject<USkeletalMeshComponent>("StaticMesh");
	OxygenManageComponent = CreateDefaultSubobject<UOxygenManageComponent>("OxygenManager");
}

void ASuitEntity::BeginPlay()
{
	Super::BeginPlay();
}

void ASuitEntity::UseOxygen()
{
	OxygenManageComponent->UseOxygen();
}

void ASuitEntity::RecoverOxygen()
{
	OxygenManageComponent->RecoverOxygen();
}

void ASuitEntity::RecoverOxygen(const float InOxygen)
{
	OxygenManageComponent->RecoverOxygen(InOxygen);
}

FOxygenUpdateDelegate& ASuitEntity::GetOxygenUpdateDelegate()
{
	return OxygenManageComponent->GetOxygenUpdateDelegate();
}

USkeletalMeshComponent* ASuitEntity::GetSkeletalMeshComponent()
{
	return SuitSkeletalComponent;
}

void ASuitEntity::Upgrade(const FInventoryData& InUpgradeData)
{
	OnUpgraded();
}

const TArray<FEquipmentUpgradeData>& ASuitEntity::GetUpgradeDatas()
{
	return UpgradeDatas;
}

void ASuitEntity::OnUpgraded()
{
}



