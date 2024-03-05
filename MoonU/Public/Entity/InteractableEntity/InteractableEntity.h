// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractableTarget.h"
#include "InteractableEntity.generated.h"

UCLASS()
class MOONU_API AInteractableEntity : public AActor, public IInteractableTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region IInteractableTarget
	virtual const FGameplayTag& GetEntityTag() override;

	virtual void OnInteracted(AActor* InstigatorActor) override;
#pragma endregion
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> InteractableStaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag EntityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 bRemainAfterInteraction : 1;
};
