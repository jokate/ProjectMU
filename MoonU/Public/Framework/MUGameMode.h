// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Interface/TimeWinder.h"
#include "MUGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API AMUGameMode : public AGameMode, public ITimeWinder
{
	GENERATED_BODY()

public :
	AMUGameMode();

protected : 
	virtual void TimeWindActivate() override;

	virtual void TimeWindDeactivate() override;
	
	virtual void RegisterTimeWindTarget(AActor* InActor) override;

	virtual void UnregisterTimeWindTarget(AActor* InActor) override;
protected :
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UTimeWindManager> TimeWindManager;
};
