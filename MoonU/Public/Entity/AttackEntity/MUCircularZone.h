// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MUAttackEntity.h"
#include "MUCircularZone.generated.h"

UCLASS()
class MOONU_API AMUCircularZone : public AMUAttackEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUCircularZone();

public:
	virtual void OnReacted( AActor* ReactedActor ) override;

	virtual bool CheckReact( AActor* ReactTarget ) const override;

	virtual TArray<AActor*> GetAttackableActorList() override;

public :
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float CheckRad = 100.f;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TObjectPtr<class USphereComponent> VisualSphereComponent;
	
};
