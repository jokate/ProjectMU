// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "Interface/InventoryOwner.h"
#include "StorageEntity.generated.h"

UCLASS()
class MOONU_API AStorageEntity : public AInteractableEntity, public IInventoryOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStorageEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

#pragma region IInventoryOwner
	virtual void OnInteracted(AActor* InstigatorActor) override;

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
