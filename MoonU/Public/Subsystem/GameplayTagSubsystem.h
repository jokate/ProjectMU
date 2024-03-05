// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UGameplayTagSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag SuitInteractionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag HelmetInteractionTag;
};
