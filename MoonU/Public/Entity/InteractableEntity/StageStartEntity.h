// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableEntity.h"
#include "StageStartEntity.generated.h"

UCLASS()
class MOONU_API AStageStartEntity : public AInteractableEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStageStartEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void OnInteracted(AActor* InstigatorActor) override;

	virtual const bool IsInteractable(AActor* InstigatorActor) override;
	
public :
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FName StageName = NAME_None;
};
