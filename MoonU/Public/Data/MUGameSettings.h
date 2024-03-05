// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MUGameSettings.generated.h"

/**
 * 
 */
static TObjectPtr<UMUGameSettings> Instance;

UCLASS(Config = Game)
class MOONU_API UMUGameSettings : public UObject
{
	GENERATED_BODY()
	
public :

	static const UMUGameSettings* Get();
	
	UPROPERTY(Config)
	FGameplayTag SuitInteractionTag;

	UPROPERTY(Config)
	FGameplayTag HelmetInteractionTag;

private:
};
