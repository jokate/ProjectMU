// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/TimeWinder.h"
#include "TimeWindManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UTimeWindManager : public UActorComponent, public ITimeWinder
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTimeWindManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TimeWindActivate() override;

	virtual void TimeWindDeactivate() override;

	virtual void RegisterTimeWindTarget(AActor* InActor) override;

	virtual void UnregisterTimeWindTarget(AActor* InActor) override;

private :
	UPROPERTY(VisibleAnywhere)
	TArray<TWeakObjectPtr<AActor>> RegisteredActors;
};
