// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MUDevSettings.generated.h"

/**
 * 
 */
UCLASS(Config = MUDevSettings, Defaultconfig, meta = (DisplayName = "MUDevSettings"))
class MOONU_API UMUDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public :
	UPROPERTY( EditAnywhere, Config, Category = "Test | Playable Character")
	TArray<int32> TestPlayableCharacterIDs;

	UPROPERTY( EditAnywhere, Config, Category = "Test | Test Mode")
	bool bIsTestModeActive = false;
};
