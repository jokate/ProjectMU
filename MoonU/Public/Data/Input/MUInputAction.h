// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "MUInputAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOONU_API UMUInputAction : public UInputAction
{
	GENERATED_BODY()
public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag GameplayTag;
};

