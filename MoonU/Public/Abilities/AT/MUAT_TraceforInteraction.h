// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "MUAT_TraceforInteraction.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionFilteringFinished, AActor*, CachedActor);

UCLASS()
class MOONU_API UMUAT_TraceforInteraction : public UAbilityTask
{
	GENERATED_BODY()
public :
	UMUAT_TraceforInteraction();
	
	static UMUAT_TraceforInteraction* CreateTask(UGameplayAbility* InAbility, float InInteractionRadius, float InLineCastLength);

protected :
	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;

	void SphereTraceForInteraction();

	void FilterInteraction(const TArray<FHitResult>& InHitResult);
	
public :
	FOnInteractionFilteringFinished InteractionCheckFinished;
protected :
	UPROPERTY()
	TObjectPtr<ACharacter> CachedOwningCharacter;
	
	UPROPERTY()
	TObjectPtr<AActor> CachedActor;

	UPROPERTY()
	float InteractionRadius;

	UPROPERTY()
	float LineCastLength;
};
