// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MUCheatSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUCheatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	virtual void Initialize(FSubsystemCollectionBase& Collection);
};
