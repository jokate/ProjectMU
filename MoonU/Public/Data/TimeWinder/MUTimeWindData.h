// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MUTimeWindData.generated.h"


USTRUCT(BlueprintType)
struct FTimeWindRecordData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	FVector Position;

	UPROPERTY(VisibleAnywhere)
	FRotator Rotation;
};
