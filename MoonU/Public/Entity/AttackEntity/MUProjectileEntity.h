// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUAttackEntity.h"
#include "Data/DataTable/MUData.h"
#include "MUProjectileEntity.generated.h"

class UProjectileMovementComponent;

UCLASS()
class MOONU_API AMUProjectileEntity : public AMUAttackEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUProjectileEntity();

	virtual void SetupProjectileInfo();
protected:
	virtual void BeginPlay() override;
	virtual TArray<AActor*> GetAttackableActorList() override;

	virtual void OnReacted(AActor* ReactedActor) override;
	virtual bool CheckReact(AActor* ReactTarget) const override;
	
public :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystemComponent> ParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly)
	FName ProjectileInfo;

	UPROPERTY(VisibleAnywhere)
	FMUProjectileInfo ProjectileInfoData;
};
