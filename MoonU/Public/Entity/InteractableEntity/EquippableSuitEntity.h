// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "Entity/SuitEntity.h"
#include "Interface/SuitEquipper.h"
#include "EquippableSuitEntity.generated.h"

UCLASS()
class MOONU_API AEquippableSuitEntity : public AInteractableEntity, public ISuitEquipper
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEquippableSuitEntity();

	virtual void BeginPlay() override;

	virtual const bool IsInteractable(AActor* InstigatorActor) override;
	
	virtual void OnInteracted(AActor* InstigatorActor) override;

#pragma region ISuitEquipper
	virtual FSuitDelegate& GetSuitEquipEvent() override;

	virtual bool GetSuitEquipped() const override;

	virtual void EquipSuit(AActor* SuitEntity) override;

	virtual AActor* UnEquipSuit() override;
#pragma endregion

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Suit Actor | Class")
	TSubclassOf<AActor> SuitActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Suit Component")
	TObjectPtr<class UMUSuitComponent> SuitComponent;

	FSuitDelegate SuitDelegate;
};
