// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "Interface/ItemGiver.h"
#include "ItemEntity.generated.h"

struct FInventorySlotData;

UCLASS()
class MOONU_API AItemEntity : public AInteractableEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemEntity();

	virtual void OnInitialize(const FName& InName);

	virtual void OnInteracted(AActor* InstigatorActor) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected :
	UPROPERTY(VisibleAnywhere)
	TArray<FInventorySlotData> InventorySlotData;
};

