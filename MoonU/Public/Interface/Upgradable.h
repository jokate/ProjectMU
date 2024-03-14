// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/MUItemData.h"
#include "UObject/Interface.h"
#include "Upgradable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUpgradable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MOONU_API IUpgradable
{
	GENERATED_BODY()

public:
	virtual void Upgrade(const FInventoryData& InUpgradeData) = 0;

	virtual const TArray<FEquipmentUpgradeData>& GetUpgradeDatas() = 0;
};
