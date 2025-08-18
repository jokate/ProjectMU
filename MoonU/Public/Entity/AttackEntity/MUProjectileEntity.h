// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUAttackEntity.h"
#include "MUProjectileEntity.generated.h"

class UProjectileMovementComponent;

UCLASS()
class MOONU_API AMUProjectileEntity : public AMUAttackEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUProjectileEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual TArray<AActor*> GetAttackableActorList() override;
	
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	FName ProjectileInfo;
};
