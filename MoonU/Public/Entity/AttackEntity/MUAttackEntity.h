// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MUAttackEntity.generated.h"

UENUM(BlueprintType)
enum class EAttackingType : uint8
{
	ENEMY,
	FRIENDLY,
	ALL
};

UCLASS()
class MOONU_API AMUAttackEntity : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUAttackEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	virtual void RegisterOwner( AActor* InSpawnedOwner );

	virtual void OnReacted( AActor* ReactedActor );

	virtual bool CheckReact( AActor* ReactTarget ) const;

	virtual void DoAttack();
public :
	UPROPERTY( EditDefaultsOnly )
	float ReactCheckInterval = 0.5f;

	UPROPERTY( EditDefaultsOnly )
	EAttackingType AttackTo = EAttackingType::ENEMY;

	UPROPERTY( EditDefaultsOnly )
	bool bHitOnce = false;

	UPROPERTY()
	TObjectPtr<AActor> SpawnedOwner;

	FTimerHandle ReactCheckTimer;

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> ReactedActors;
};
