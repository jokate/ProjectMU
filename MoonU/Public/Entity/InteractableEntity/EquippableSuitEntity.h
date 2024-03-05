﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "EquippableSuitEntity.generated.h"

UCLASS()
class MOONU_API AEquippableSuitEntity : public AInteractableEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquippableSuitEntity();

public:
	virtual void OnInteracted(AActor* InstigatorActor) override;
};
