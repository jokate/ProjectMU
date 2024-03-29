﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/MUItemData.h"
#include "GameFramework/Actor.h"
#include "Interface/Equippable.h"
#include "Interface/Upgradable.h"
#include "EquipmentEntity.generated.h"

UCLASS()
class MOONU_API AEquipmentEntity : public AActor, public IUpgradable, public IEquippable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquipmentEntity();

protected:

#pragma region IUpgradable
	virtual void Upgrade(const FInventoryData& InUpgradeData) override;

	virtual const TArray<FEquipmentUpgradeData>& GetUpgradeDatas() override;
#pragma endregion

	virtual void OnUpgrade();

#pragma region IEquippable
	virtual const FGameplayTag& GetEquipEntityTag() override;
#pragma endregion
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment Mesh")
	TObjectPtr<UStaticMeshComponent> EquipmentStaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equipement Upgrade")
	TArray<FEquipmentUpgradeData> UpgradeData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment Tag")
	FGameplayTag EquipmentTag;
};
