// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/OxygenManager.h"
#include "Interface/SpaceTraveler.h"
#include "Interface/SuitEquipper.h"
#include "MUSuitComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOONU_API UMUSuitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMUSuitComponent(); 
	
	virtual bool GetSuitEquipped() const;

	virtual void EquipSuit(AActor* SuitEntity);

	virtual AActor* UnEquipSuit();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:	
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly, Category = "Suit Entity")
	TObjectPtr<AActor> EquippedSuitEntity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Suit Socket Name")
	FName SuitSocket = NAME_None;
};
