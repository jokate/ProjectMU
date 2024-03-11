// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "Data/Item/MUItemData.h"
#include "InteractableItemEntity.generated.h"

UCLASS()
class MOONU_API AInteractableItemEntity : public AInteractableEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableItemEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MakeItemInfo();

public:
	virtual void OnInteracted(AActor* InstigatorActor) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemLootingName;

	UPROPERTY(EditDefaultsOnly)
	uint8 bIsLootingItem : 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FInventoryData> InventoryData;
};
