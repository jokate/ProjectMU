// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "InteractableWidgetBoardEntity.h"
#include "Interface/InventoryOwner.h"
#include "StorageEntity.generated.h"

UCLASS()
class MOONU_API AStorageEntity : public AInteractableWidgetBoardEntity, public IInventoryOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStorageEntity();
	
public:
	
#pragma region IInventoryOwner
	UFUNCTION(BlueprintCallable)
	virtual void OwnInventory(const FInventoryData& Item) override;

	virtual void OwnInventoryByIndex(const FInventoryData& Item, int32 Index) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisOwnInventory(const FInventoryData& Item) override;

	virtual void DisownInventoryByIndex(int32 Index) override;

	virtual int32 GetMaxStorageAmount() const override;

	virtual const TArray<FInventoryData>& GetTotalInventoryData() override;
#pragma endregion

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<class UInventoryComponent> InventoryComponent;
};
