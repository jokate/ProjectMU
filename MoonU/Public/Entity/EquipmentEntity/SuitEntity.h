// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentEntity.h"
#include "GameFramework/Actor.h"
#include "Interface/OxygenManager.h"
#include "Interface/Suit.h"
#include "SuitEntity.generated.h"

UCLASS()
class MOONU_API ASuitEntity : public AActor, public IOxygenManager, public ISuit, public IUpgradable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASuitEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region IOxygenManager
	virtual void UseOxygen() override;

	virtual void RecoverOxygen() override;

	virtual void RecoverOxygen(const float InOxygen) override;

	virtual FOxygenUpdateDelegate& GetOxygenUpdateDelegate() override;
#pragma endregion

	virtual USkeletalMeshComponent* GetSkeletalMeshComponent() override;

#pragma region Upgradable
	virtual void Upgrade(const FInventoryData& InUpgradeData) override;

	virtual const TArray<FEquipmentUpgradeData>& GetUpgradeDatas() override;
#pragma endregion

	void OnUpgraded();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UOxygenManageComponent> OxygenManageComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> SuitSkeletalComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Upgraded Option")
	TArray<FEquipmentUpgradeData> UpgradeDatas;
};
