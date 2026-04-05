// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Interface/ObjectPoolingTarget.h"
#include "MUAttackEntity.generated.h"

UENUM(BlueprintType)
enum class EAttackingType : uint8
{
	ENEMY,
	FRIENDLY,
	ALL
};

UCLASS()
class MOONU_API AMUAttackEntity : public AActor, public IAbilitySystemInterface, public IObjectPoolingTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUAttackEntity();
	
	virtual void RegisterOwner( AActor* InSpawnedOwner );
	
	virtual void ReturnToPooling() override;
	
	virtual bool CanActivateObject() override;

	virtual void ActivateObject(FTransform Transform) override;
	
protected:
	
	UPROPERTY( EditDefaultsOnly )
	EAttackingType AttackTo = EAttackingType::ENEMY;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void LifeSpanExpired() override;
public :
	UPROPERTY()
	TWeakObjectPtr<AActor> SpawnedOwner;

	UPROPERTY()
	bool bIsActive = false;
};
