// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/EquipmentOwner.h"
#include "EquipmentComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UEquipmentComponent : public UActorComponent, public IEquipmentOwner
{
	GENERATED_BODY()

public :

	virtual void EquipItem(AActor* InActor) override;

	virtual const FGameplayTag& GetEquippingItemTag() override;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Current Equipment Actor")
	TObjectPtr<AActor> EquipmentActor;
};
