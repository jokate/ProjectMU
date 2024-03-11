// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MUWidgetToCheck.generated.h"

/**
 * 
 */
UCLASS()
class MOONU_API UMUWidgetToCheck : public UPrimaryDataAsset
{
	GENERATED_BODY()
public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGameplayTag> WidgetGameplayTag;
};
