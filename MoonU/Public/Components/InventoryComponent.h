﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Item/MUItemData.h"
#include "Interface/InventoryOwner.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UInventoryComponent : public UActorComponent, public IInventoryOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
public :
	virtual void OwnInventory(const FItemDataRow& Item, const int32 ItemAmount) override;

	virtual void DisOwnInventory(const FItemDataRow& Item, const int32 ItemAmount) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FInventoryData> InventoryData;
};