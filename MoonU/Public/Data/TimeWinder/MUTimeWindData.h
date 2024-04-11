// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MUTimeWindData.generated.h"

USTRUCT(BlueprintType)
struct FTimeWindMontageRecordData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<UAnimMontage> Montage;

	UPROPERTY(VisibleAnywhere)
	float MontagePosition;
};

USTRUCT(BlueprintType)
struct FTimeWindRecordData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	FVector Position;

	UPROPERTY(VisibleAnywhere)
	FRotator Rotation;

	UPROPERTY(VisibleAnywhere)
	FTimeWindMontageRecordData MontageRecordData;
};
