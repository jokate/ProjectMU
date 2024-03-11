// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/Item/MUItemData.h"
#include "Interface/InventoryOwner.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API     UInventoryComponent : public UActorComponent, public IInventoryOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
public :
	UFUNCTION(BlueprintCallable)
	virtual void OwnInventory(const FInventoryData& Item) override;

	UFUNCTION(BlueprintCallable)
	virtual void OwnInventoryByIndex(const FInventoryData& Item, int32 Index) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisOwnInventory(const FInventoryData& Item) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisownInventoryByIndex(int32 Index) override;
	
	virtual int32 GetMaxStorageAmount() const override;
	
	virtual const TArray<FInventoryData>& GetTotalInventoryData() override;

protected:
	void OnInventoryUpdated();
	// Called when the game starts
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FInventoryData> InventoryData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Max Amount")
	int32 MaxInventoryAmount = 20;
};
