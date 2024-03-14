// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/EquipmentEntity/EquipmentEntity.h"


// Sets default values
AEquipmentEntity::AEquipmentEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EquipmentStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("EquipmentMeshComponent");
}

void AEquipmentEntity::Upgrade(const FInventoryData& InUpgradeData)
{
	OnUpgrade();
}

const TArray<FEquipmentUpgradeData>& AEquipmentEntity::GetUpgradeDatas()
{
	return UpgradeData;
}

void AEquipmentEntity::OnUpgrade()
{
}


