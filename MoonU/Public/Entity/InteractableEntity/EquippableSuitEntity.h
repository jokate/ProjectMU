// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "Entity/SuitEntity.h"
#include "EquippableSuitEntity.generated.h"

UCLASS()
class MOONU_API AEquippableSuitEntity : public ASuitEntity, public IInteractableTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquippableSuitEntity();

	virtual const bool IsInteractable(AActor* InstigatorActor) override;
	
	virtual const FGameplayTag& GetEntityTag() override;
public:
	virtual void OnInteracted(AActor* InstigatorActor) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteracted_BP(AActor* InstigatorActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tag")
	FGameplayTag Tag;
};
