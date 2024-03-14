// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/OxygenManager.h"
#include "Interface/SpaceTraveler.h"
#include "MUSuitComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOONU_API UMUSuitComponent : public UActorComponent, public ISpaceTraveler
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMUSuitComponent();

	void SetSuitEquipped(bool InEquipped);

	void SetHeadEquipped(bool InEquipped);

	virtual bool GetSuitEquipped() const;
	virtual bool GetHeadEquipped() const;
	
#pragma region ISpaceTraveler
	virtual void OnCharacterInBasement() override;

	virtual void OnCharacterOutBasement() override;
#pragma endregion 
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void OnUpdateOxygen();

protected:	
	UPROPERTY(SaveGame, VisibleAnywhere, Category = "Suit Activated")
	uint8 bSuitEquipped : 1;

	UPROPERTY(SaveGame, VisibleAnywhere, Category = "Head Activated")
	uint8 bHeadEquipped : 1;

	UPROPERTY(SaveGame, VisibleAnywhere, Category = "Suit Entity")
	TObjectPtr<AActor> EquippedSuitEntity;
	
};
