// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "InteractableWidgetBoardEntity.generated.h"

UCLASS()
class MOONU_API AInteractableWidgetBoardEntity : public AInteractableEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableWidgetBoardEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnInteracted(AActor* InstigatorActor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable Entity Name")
	FName EntityName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Tag")
	FGameplayTag UIGameplayTag;
};
