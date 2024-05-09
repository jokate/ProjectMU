// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "MUGC_PlayTimeline.generated.h"

/**
 * 
 */
UCLASS()
class AMUGC_PlayTimeline : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public :
	AMUGC_PlayTimeline();

protected :
	virtual void BeginPlay() override;

	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	
	UFUNCTION()
	void OnFinishedTimeline();
	
	
	UFUNCTION()
	void OnValueChanged(float InValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnValueChanged_BP(float InValue);
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimelineComponent> TimelineComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UCurveFloat> TimelineCurve;
};
