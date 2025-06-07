// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GC/MUGC_PlayTimeline.h"
#include "MUGC_IndicatorCam.generated.h"

UCLASS()
class MOONU_API AMUGC_IndicatorCam : public AMUGC_PlayTimeline
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMUGC_IndicatorCam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	
};
