// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MUSkillIndicator.generated.h"

UCLASS()
class MOONU_API AMUSkillIndicator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUSkillIndicator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void CalculateIndicatorMesh();

public :
	UPROPERTY( EditDefaultsOnly )
	TObjectPtr<UStaticMeshComponent> IndicatorMeshComponent;

	UPROPERTY( EditDefaultsOnly )
	TObjectPtr<class UDecalComponent> IndicatorDecalComponent;
};
