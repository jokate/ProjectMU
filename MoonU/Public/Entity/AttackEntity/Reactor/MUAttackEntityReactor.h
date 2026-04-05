// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/AttackEntity/MUAttackEntity.h"
#include "MUAttackEntityReactor.generated.h"

UCLASS()
class MOONU_API AMUAttackEntityReactor : public AMUAttackEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUAttackEntityReactor();

	virtual void ActivateObject(FTransform Transform) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

#pragma region ObjectPoolingTarget

	virtual void ReturnToPooling() override;

	virtual bool CanActivateObject() override;

#pragma endregion

	virtual void OnReacted( AActor* ReactedActor );

	virtual bool CheckReact( AActor* ReactTarget ) const;

	virtual void DoAttack();

	virtual TArray<AActor*> GetAttackableActorList();
	
	public :
		UPROPERTY( EditDefaultsOnly )
	float ReactCheckInterval = 0.5f;
	
public:
	FTimerHandle ReactCheckTimer;

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> ReactedActors;

	UPROPERTY( EditDefaultsOnly )
	bool bHitOnce = false;
};
