// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagSubsystem.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class MOONU_API UGameplayTagSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Config)
	FGameplayTag SuitInteractionTag;
};
